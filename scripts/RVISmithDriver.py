import os
import sys
import shutil
import subprocess
import argparse
from tqdm import tqdm
import pandas as pd
import datetime
import json
from concurrent.futures import ProcessPoolExecutor
sys.path = [os.path.abspath( os.path.dirname(os.path.abspath(__file__))  )] + sys.path
from Config import Config
from TestGen import getSeed, getDataLength, getSeqLength, getRoot
from DiffEval import oneEval, res_dict

# global vars
dt = "" # data time now
rvismith_path = ""
config_path = ""
output_path = ""
number = 0
segment = False # whether segment load-store intrinsics included
policy = False # whether load-store intrinsics with policy suffixes included
overloaded = False #whether overloaded load-store intrinsics included

# randomly generate a arg group for one test case generation
def get_a_arg(_):
    seed, data_len, seq_len, root = getSeed(), getDataLength(), getSeqLength(), getRoot()
    arg  = {'seed': [seed], 'data_length': [data_len], \
            'sequence_length': [seq_len], 'root': [root] }
    return arg

# arg -> str
def hash_arg(arg: dict):
    res = f"{arg['seed'][0]}-{arg['data_length'][0]}-{arg['sequence_length'][0]}-{arg['root'][0]}"
    return res

# args generation in parallel
def gen_args_parallel():
    print("start generating args for rvismith...")
    args = []
    with ProcessPoolExecutor() as executor:
        args = list( tqdm(executor.map(get_a_arg, [None] * number), total=number ) )
    csv_file = os.path.join(output_path, dt, "args.csv")
    dfs = pd.concat( (pd.DataFrame(item) for item in args), ignore_index=True)
    dfs.to_csv(csv_file, mode='w', header=False)
    print(f"args in: {csv_file}\n")
    return args

def gen_cmd_rvismith(arg: dict):
    code_dir = os.path.join(output_path, dt, "tmp", hash_arg(arg))
    cmd = rvismith_path
    if(segment): cmd += " --segment "
    if(policy): cmd += " --policy "
    if(overloaded): cmd += " --overloaded "
    cmd += f" --seed {arg['seed'][0]}"\
        + f" --data_length {arg['data_length'][0]}"\
        + f" --sequence_length {arg['sequence_length'][0]}"\
        + f" --root {arg['root'][0]}"\
        + f" --output {code_dir}"
    return cmd

""" (def in CollectFailCases.py)
res_dict = {0:"success", 1:"all compile error", 2:"calculation error", \
            3:"emulator dumped", 4:"compiler dumped", 5:"RVISmith failed", \
            6:"partial compile error", 7:"other"}
"""
# given an arg, use rvismith generate a case and test this case
# return evaluation result
def one_test(config:Config, arg: dict):
    code_dir = os.path.join(output_path, dt, "tmp", hash_arg(arg))
    error_dir = os.path.join(output_path, dt, "error_log", hash_arg(arg))
    os.mkdir(code_dir)

    # test case generation
    cmd = gen_cmd_rvismith(arg)
    result = subprocess.run([cmd], shell=True, capture_output=True, text=True )
    if (result.stderr.strip() != ""):
        os.mkdir(error_dir)
        logf = open(os.path.join(error_dir, "rvismith.log"), "w", encoding="utf-8" )
        logf.write(cmd + "\n")
        logf.write(result.stdout)
        logf.write(result.stderr)
        logf.close()
        shutil.rmtree(code_dir)
        res = {"allin":5, "random":5, "unit":5, "emi":5}
        if set(arg).intersection(res):
            raise ValueError("Dictionaries have overlapping keys!")
        return {**arg, **res}
    
    # evaluation: diff
    res1, logtext1, out1 = oneEval(config, code_dir, "allin")
    res2, logtext2, out2 = oneEval(config, code_dir, "random")
    res3, logtext3, out3 = oneEval(config, code_dir, "unit")
    if( (res1==0 and res2==0 and res3 == 0) != 1 ):
        os.mkdir(error_dir)
        logf = open(os.path.join(error_dir, "stderr_message.log"), "w+", encoding="utf-8" )
        logf.write(cmd + "\n")
        logf.write("allin mode:\n")
        logf.write(logtext1 + "\n")
        logf.write("random mode:\n")
        logf.write(logtext2 + "\n")
        logf.write("unit mode:\n")
        logf.write(logtext3 + "\n")
        logf.close()
    
    # evaluation: emi
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
    
    # if all success, clean the tmp file
    if(res1 == 0 and res2 == 0 and res3 == 0 and emi_res == 0):
        shutil.rmtree(code_dir)
    
    res = {"allin":res1, "random":res2, "unit":res3, "emi":emi_res}
    if set(arg).intersection(res):
        raise ValueError("Dictionaries have overlapping keys!")
    return {**arg, **res}


def eval_parallel(config: Config, args: list):
    print("start evaluation...")
    eval_result_path = os.path.join( output_path, dt )

    res = []
    with ProcessPoolExecutor() as executor:
        res = list( tqdm(executor.map(one_test, [config for i in range(number)], args), total=number ) )

    csv_file = os.path.join(output_path, dt, "res.csv")
    dfs = pd.concat( (pd.DataFrame(item) for item in res), ignore_index=True)
    dfs.to_csv(csv_file, mode='w', header=False)

    sum_log = open(os.path.join(eval_result_path, "diff.log"), "w", encoding="utf-8")
    emi_log = open(os.path.join(eval_result_path, "emi.log"), "w", encoding="utf-8")
    for n in range(number):
        tbd = {"id":hash_arg(res[n]), "allin":res[n]["allin"], "random":res[n]["random"], "unit":res[n]["unit"], "emi":res[n]["emi"]}
        if( tbd["allin"]!=0 or tbd["random"]!=0 or tbd["unit"]!=0 or tbd["emi"]!=0 ):
            sum_log.write(f"{tbd['id']}, {res_dict[tbd['allin']]}, {res_dict[tbd['random']]}, {res_dict[tbd['unit']]}, {res_dict[tbd['emi']]}\n")
        if( tbd["emi"] != 0 ):
            emi_log.write(f"{tbd['id']}, {res_dict[tbd['emi']]}\n")
            tbd["emi"] = 7
    emi_log.close()
    sum_log.close()

    print(f"evaluation result in: {csv_file}")


# preparation
def setup():
    global rvismith_path, config_path, output_path, number, segment, policy, overloaded, dt
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--number', default=10, help="test case number")
    parser.add_argument('-r', '--rvismith_path', required=True, help="path to rvismith")
    parser.add_argument('-c', '--config_path', required=True, help="evaluation config path")
    parser.add_argument('-o', '--output_path', default="./rvismith_eval", help="output path of test cases")
    #parser.add_argument('--segment', action="store_true", help="whether segment load-store intrinsics included")
    parser.add_argument('--policy', action="store_true", help="whether load-store intrinsics with policy suffixes included")
    parser.add_argument('--overloaded', action="store_true", help="whether overloaded load-store intrinsics included")
    
    args = parser.parse_args()
    if (os.path.exists(args.rvismith_path) == False):
        print('please check the path to rvismith.', file = sys.stderr)
        sys.exit(1)
    if (os.path.exists(args.config_path) == False):
        print('please check the path to evaluation config.', file = sys.stderr)
        sys.exit(1)
    if (os.path.exists(args.output_path) == False):
        os.mkdir(args.output_path)
    
    rvismith_path = os.path.abspath(args.rvismith_path)
    config_path = os.path.abspath(args.config_path)
    output_path = os.path.abspath(args.output_path)
    number = int(args.number) if int(args.number) > 0 else 10
    #segment = args.segment
    segment = True # always true is recommended
    policy = args.policy
    overloaded = args.overloaded
    dt = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
    
    if (os.path.exists(os.path.join(output_path, dt)) == False):
        os.mkdir( os.path.join(output_path, dt) )
    
    os.mkdir( os.path.join(output_path, dt, "error_log") ) # for error message
    os.mkdir( os.path.join(output_path, dt, "tmp") ) # for cache

    with open( os.path.join(output_path, dt, "gen_config.json"), "w", encoding="utf-8") as json_file:
        content = ""
        try:
            with open(config_path, "r", encoding="utf-8") as f:
                content = f.read()
        except:
            content = ""
        data = { "dt": dt, \
            "rvismith_path": rvismith_path, \
            "config_path": config_path, \
            "config_content": content, \
            "output_path": output_path, \
            "number": number, \
            "segment": 1 if segment else 0, \
            "policy": 1 if policy else 0, \
            "overloaded": 1 if overloaded else 0
            }
        json.dump(data, json_file, indent=4 )


if __name__ == "__main__":
    setup()
    eval_parallel(Config(config_path), gen_args_parallel())