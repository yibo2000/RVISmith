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
from TestGen import getSeed, getDataLength, getSeqLength
from DiffEval import TestResult, oneEval

# global vars
dt = "" # data time now
rvismith_path = ""
config_path = ""
output_path = ""
number = 0

# randomly generate a arg group for one test case generation
def get_a_arg(_):
    seed, data_len, seq_len = getSeed(), getDataLength(), getSeqLength()
    import random
    arg = { 
        "seed": [f"0x{random.getrandbits(32):08x}"],
        "data_length": [str(random.randint(1, 128))],
        "sequence_length": [str(random.randint(1, 5))],
    }
    # arg = {'seed': [seed], 'data_length': [data_len], 'sequence_length': [seq_len] }
    return arg

# arg -> str
def hash_arg(arg: dict):
    res = f"{arg['seed'][0]}-{arg['data_length'][0]}-{arg['sequence_length'][0]}"
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
    cmd += f" --seed {arg['seed'][0]}"\
        + f" --data_length {arg['data_length'][0]}"\
        + f" --sequence_length {arg['sequence_length'][0]}"\
        + f" --output {code_dir}"
    return cmd

# given an arg, use rvismith generate a case and test this case
# return evaluation result
def one_test(config:Config, arg: dict):
    code_dir = os.path.join(output_path, dt, "tmp", hash_arg(arg))
    os.mkdir(code_dir)

    # test case generation
    cmd = gen_cmd_rvismith(arg)
    result = subprocess.run([x for x in cmd.split(" ") if x], capture_output=True, text=True )
    if (result.stderr.strip() != ""):
        logf = open(os.path.join(code_dir, "rvismith.log"), "w", encoding="utf-8" )
        logf.write(cmd + "\n")
        logf.write(result.stdout)
        logf.write(result.stderr)
        logf.close()
        shutil.rmtree(code_dir)
        res = {"res": TestResult.FuzzerFail}
        if set(arg).intersection(res):
            raise ValueError("Dictionaries have overlapping keys!")
        return {**arg, **res}
    
    # evaluation: diff
    res, logtext = oneEval(config, code_dir)
    if(res != TestResult.Pass):
        logf = open(os.path.join(code_dir, "stderr_message.log"), "w+", encoding="utf-8" )
        logf.write(cmd + "\n")
        logf.write(logtext + "\n")
        logf.close()
    
    # if all success, clean the tmp file
    if(res == TestResult.Pass): shutil.rmtree(code_dir)
    
    res = {"res": res}
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
    for n in range(number):
        tbd = {"id":hash_arg(res[n]), "res":res[n]["res"]}
        if( tbd["res"]!= TestResult.Pass):
            sum_log.write(f"{tbd['id']}, {tbd["res"]}\n")
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
    dt = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
    
    if (os.path.exists(os.path.join(output_path, dt)) == False):
        os.mkdir( os.path.join(output_path, dt) )
    
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
            }
        json.dump(data, json_file, indent=4 )


if __name__ == "__main__":
    setup()
    eval_parallel(Config(config_path), gen_args_parallel())