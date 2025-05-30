import os
import sys
import shutil
import subprocess
import argparse
from tqdm import tqdm
import numpy as np
import json
import pandas as pd
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

sys.path = [os.path.abspath( os.path.dirname(os.path.abspath(__file__))  )] + sys.path
from Config import Config

testcode_path = ""
eval_result_path = ""
config_path = ""

res_dict = {0:"success", 1:"all compile error", 2:"calculation error", \
            3:"emulator dumped", 4:"compiler dumped", 5:"RVISmith failed", \
            6:"partial compile error", 7:"other", 8:"timeout"}

def oneEval(config:Config, code_dir:str, mode:str = "allin"):
    # init
    code_out = ""

    if( len(os.listdir(code_dir)) <= 1 ): 
        return 5, res_dict[5], code_out # RVISmith failed, continue
    
    res = 0 # result for test code: n
    logtext = "" # log
    stdout = []
    compile_run_success = []
    # compile and run
    out_path = os.path.join(code_dir, f"{mode}.out")
    for i in range(0, len( config.compiler_paths)):
        # compile
        cmd_compile = config.compiler_paths[i] + " " + config.compiler_flags[i] + " " + os.path.join(code_dir, f"{mode}.c") + " -o " + out_path
        
        try:
            result_compile = subprocess.run([cmd_compile], shell=True, capture_output=True, text=True, timeout=300 )
        except: # timeout
            return 8, res_dict[8], ""

        if( "dump" in result_compile.stderr.lower() or \
        "core" in result_compile.stderr.lower() or \
        "segment" in result_compile.stderr.lower()):
            logtext += cmd_compile+"\n"
            logtext += result_compile.stderr
            res = 4
        elif( "error" in result_compile.stderr or "Error" in result_compile.stderr):
            # compiler error
            logtext += cmd_compile+"\n"
            logtext += result_compile.stderr
        else: # run
            # run the test code
            cmd_run = f"{config.sim_path} {config.sim_flag} {out_path}" # if emulator needs flags, fix this line
            
            try:
                result_run = subprocess.run([cmd_run], shell=True, capture_output=True, text=True, timeout=300)
            except: # timeout
                return 8, res_dict[8], ""

            if( 'dump' in result_run.stderr.strip().lower() or "core" in result_run.stderr.strip().lower() or "illegal" in result_run.stderr.strip().lower()):
                # sim dumped
                res = 3
                logtext += cmd_compile+"\n"
                logtext += cmd_run+"\n"
                logtext += result_run.stderr
                logtext += "\n"
            elif(result_run.stderr.strip() != ""):
                res = 7 # other
                logtext += cmd_compile+"\n"
                logtext += cmd_run+"\n"
                logtext += result_run.stderr
                logtext += "\n"
            else:
                # compile and run success
                #with open(os.path.join(res_dir, f"{mode}{i}.txt"), "w", encoding="utf-8" ) as outf:
                    #outf.write(result_run.stdout)
                stdout.append(result_run.stdout.strip())
                compile_run_success.append(i)
    
    if(os.path.exists(out_path)): os.remove(out_path)
    if( len(compile_run_success) == 0 and res == 0 ):
        res = 1 # all compile error
        logtext += res_dict[1]+"\n"
    if( len(compile_run_success) < len( config.compiler_paths) and res == 0 ):
        res = 6 # partial compile error
        logtext += res_dict[6]+"\n"
    if( res != 0 ):
        return res, logtext, code_out

    # differential testing
    assert( len(stdout) == len(compile_run_success) )
    length = len(compile_run_success)
    if(length >= 2 and res == 0):
        for i in range(0, length):
            for j in range(i+1, length):
                #try:
                #different, lineNum = JudgeResults.judge( os.path.join(res_dir, f"{mode}{i}.txt"), os.path.join(res_dir, f"{mode}{j}.txt") )
                different = (stdout[i] != stdout[j])
                if(different == True):
                    res = 2 # calculation error
                    logtext += f"{i} and {j}, calculation error.\n"
                    # logtext += f"calculation error: in line {lineNum}.\n"
    
    if(res == 0): 
        logtext += res_dict[0]+"\n"
        code_out = stdout[0]

    return res, logtext, code_out

'''
def emiEval(idx:int):
    # for all success idx
    # init
    # code_dir = os.path.join(testcode_path, "code", str(idx))
    res_dir = os.path.join(eval_result_path, "eval_result", str(idx))

    tbd = ["allin0.txt", "unit0.txt", "random0.txt"]
    different1, lineNum1 = JudgeResults.judge( os.path.join(res_dir, tbd[0]), os.path.join(res_dir, tbd[1]) )
    different2, lineNum2 = JudgeResults.judge( os.path.join(res_dir, tbd[0]), os.path.join(res_dir, tbd[2]) )
    different3, lineNum3 = JudgeResults.judge( os.path.join(res_dir, tbd[1]), os.path.join(res_dir, tbd[2]) )
    
    if( different1 == 0 and different2 == 0 and different3 == 0 ):
        return 0 # success
    else:
        return 2 # calculation error
'''

def once_eval(config:Config, n:int):
    code_dir = os.path.join(testcode_path, "code", str(n))
    res1, logtext1, out1 = oneEval(config, code_dir, "allin")
    res2, logtext2, out2 = oneEval(config, code_dir, "random")
    res3, logtext3, out3 = oneEval(config, code_dir, "unit")
    
    if( (res1==0 and res2==0 and res3 == 0) != 1 ):
        # code_dir = os.path.join(testcode_path, "code", str(n))
        res_dir = os.path.join(eval_result_path, "error_log", str(n))
        if( os.path.exists(res_dir) == False ): os.mkdir( res_dir )
        else:
            shutil.rmtree(res_dir)
            os.mkdir( res_dir )
        logf = open(os.path.join(res_dir, "stderr_message.log"), "w+", encoding="utf-8" )
        logf.write("allin mode:\n")
        logf.write(logtext1 + "\n")

        logf.write("random mode:\n")
        logf.write(logtext2 + "\n")

        logf.write("unit mode:\n")
        logf.write(logtext3 + "\n")
        logf.close()

    emi_res = 0
    if( res1 == res2 and res2 == res3 and res3 == res1 ):
        # res1 == res2 == res3
        if (res1 == 0):
            if( out1 == out2 and out2 == out3 and out3 == out1):
                emi_res = 0 # success
            else:
                emi_res = 2 # calculation
    else: # other
        emi_res = 7
    

    '''if (res1 == 0 and res2 == 0 and res3 == 0 and emi_res == 0):
        res_dir = os.path.join(eval_result_path, "success_output", str(n))
        if( os.path.exists(res_dir) == False ): os.mkdir( res_dir )
        logf = open(os.path.join(res_dir, "success.log"), "w", encoding="utf-8" )
        logf.write(out1)
        logf.close()'''

    return {"allin":res1, "random":res2, "unit":res3, "emi":emi_res}


def diffTesting(config:Config, N:int):
    if( os.path.exists(os.path.join(eval_result_path, "error_log")) == False ): 
        os.mkdir( os.path.join(eval_result_path, "error_log") )
    if( os.path.exists(os.path.join(eval_result_path, "success_output")) == False ): 
        os.mkdir( os.path.join(eval_result_path, "success_output") )
    # N: max test code number
    if( N == -1 ): N = 10
    # generate test cases
    sum_log = open(os.path.join(eval_result_path, "diff.log"), "w", encoding="utf-8")
    emi_log = open(os.path.join(eval_result_path, "emi.log"), "w", encoding="utf-8")

    res = []
    with ProcessPoolExecutor() as executor:
        res = list( tqdm(executor.map(once_eval, [config for i in range(N)], range(N)), total=N ) )

    data_res = []
    for n in range(N):
        tbd = {"id":n, "allin":res[n]["allin"], "random":res[n]["random"], "unit":res[n]["unit"], "emi":res[n]["emi"]}
        if( tbd["allin"]!=0 or tbd["random"]!=0 or tbd["unit"]!=0 or tbd["emi"]!=0 ):
            sum_log.write(f"{n}, {res_dict[tbd['allin']]}, {res_dict[tbd['random']]}, {res_dict[tbd['unit']]}, {res_dict[tbd['emi']]}\n")
        if( tbd["emi"] != 0 ):
            emi_log.write(f"{n}, {res_dict[tbd['emi']]}\n")
            tbd["emi"] = 7
        data_res.append( tbd )

    args = pd.read_csv( os.path.join(testcode_path, "args.csv"), names=["id", "seed", "data_length", "sequence_length", "root"], header=None)
    dfs = pd.DataFrame(data=data_res)
    combined_df = pd.merge( args, dfs, on="id" )
    # args.set_index("id")
    # dfs.set_index("id")
    # combined_df = pd.concat( [args, dfs], axis=1 )
    combined_df.to_csv(os.path.join(eval_result_path, "res.csv"), mode='w', header=False, index=False)
    emi_log.close()
    sum_log.close()


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--testcode_path', required=True, help="test code path")
    parser.add_argument('-o', '--eval_result_path', required=True, help="evaluation result path")
    parser.add_argument('-c', '--config_path', required=True, help="evaluation config path")
    args = parser.parse_args()

    testcode_path = args.testcode_path
    eval_result_path = args.eval_result_path
    config_path = args.config_path

    if (not args.testcode_path) or (os.path.exists(args.testcode_path) == False):
        print('please check the path of test code.', file = sys.stderr)
        sys.exit(1)
    if( os.path.exists(os.path.join(testcode_path, "code")) == False ):
        print(f"no test code in path: {testcode_path}")
        sys.exit(1)
    total_steps = len(os.listdir(os.path.join(testcode_path, "code")))
    if( os.path.exists(os.path.join(eval_result_path)) == False ): 
        os.mkdir( os.path.join(eval_result_path) )

    if( os.path.exists(os.path.join(eval_result_path, "res.csv")) == True ):
        print(f"an evaluation result is existed before evaluation in: {eval_result_path}")
        exit(1)

    config = Config(config_path)
    print("Start evaluation...")
    
    diffTesting(config, total_steps)
