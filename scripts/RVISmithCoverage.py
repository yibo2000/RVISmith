# intrinsic coverage script for RVISmith
import re
import os
import sys
import datetime
from concurrent.futures import ProcessPoolExecutor
from tqdm import tqdm
import shutil
import subprocess
import argparse
import json
import pandas as pd
import time
NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
from RVISmithDriver import hash_arg
from TestGen import getSeed, getRoot
assert sys.version_info >= (3, 10)

rvismith_path = "/home/RVISmith-1.0.0-ubuntu-24.04-x86_64/bin/rvismith"
mode = 0
code_number = 500
tmp_dir = ""

under_test_list_file = "" # path to `merged.txt` that contains rvv definitions under test ( see `README.md` in `rvv-doc`)
segment = True # whether segment load-store intrinsics included
policy = False # whether load-store intrinsics with policy suffixes included
overloaded = False #whether overloaded load-store intrinsics included
def set_gen_config(mode: int):
    """
    mode = 0: explicit; 
    mode = 1: explicit with policy; 
    mode = 2: implicit; 
    mode = 3: implicit with policy; 
    mode = 4: all; 
    mode = other: error.
    """
    global under_test_list_file, segment, policy, overloaded
    segment = True
    match mode:
        case 0:
            under_test_list_file = os.path.join(NOWPATH, '../rvv-doc/rvv-intrinsic-list/0-explicit/merged.txt')
            policy = False
            overloaded = False
        case 1:
            under_test_list_file = os.path.join(NOWPATH, '../rvv-doc/rvv-intrinsic-list/1-explicit-policy/merged.txt')
            policy = True
            overloaded = False
        case 2:
            under_test_list_file = os.path.join(NOWPATH, '../rvv-doc/rvv-intrinsic-list/2-implicit/merged.txt')
            policy = False
            overloaded = True
        case 3:
            under_test_list_file = os.path.join(NOWPATH, '../rvv-doc/rvv-intrinsic-list/3-implicit-policy/merged.txt')
            policy = True
            overloaded = True  
        case 4:
            under_test_list_file = os.path.join(NOWPATH, '../rvv-doc/rvv-intrinsic-list/4-all/merged.txt')
            policy = True
            overloaded = True 
        case _:
            exit(1)


def get_total_number():
    res = 0
    with open(under_test_list_file, "r", encoding="utf-8") as file:
        for line in file:
            if(line.strip() != ""): res += 1
    return res

def rm_space_str(input_str: str):
    '''
    remove the spaces
    '''
    return re.sub(r'\s+', '', input_str).strip()

def intrinsic_matcher(code: str):
    """
    input: code snippet
    output: a list of matched rvv intrinsic names (with a left parenthesis)
    """
    code = rm_space_str(code)
    pattern = r"__riscv_[0-9a-z_]+\("
    return re.findall(pattern, code)

def get_init_dict():
    """
    preparation before obtain coverage
    { intrinsic:
        {
        "weight": number of matches in merged.txt (for overloaded intrinsics),\
        "count": cover count
        }
    }
    """
    res = {}
    with open(under_test_list_file, "r", encoding="utf-8") as file:
        for line in file:
            lst = intrinsic_matcher(line)
            for item in lst:
                if item in res:
                    res[item]["weight"] += 1
                else:
                    res[item] = {"weight": 1, "count": 0}
    return res
init_dict = {}

"""
rvv intrinsic coverage:
coverage = sum min(count, weight) / sum weight
"""
def api_coverage(ut_dict: dict):
    sum_count = 0
    sum_weight = 0
    for key in ut_dict.keys():
        sum_count += min( ut_dict[key]["count"] , ut_dict[key]["weight"] )
        sum_weight += ut_dict[key]["weight"]
    return float (sum_count) / float (sum_weight), sum_count, sum_weight


"""
input: code paths
output: a dict with counts and weights
"""
def get_counts(codepaths: list):
    # sequential code
    ut_dict = {}
    # other_dict = set() # matched rvv intrinsics, but not under test
    for path in codepaths:
        with open(path, "r", encoding="utf-8") as f:
            code = f.read()
            matches = intrinsic_matcher(code)
            for rvv in matches:
                if rvv in ut_dict:
                    ut_dict[rvv]["count"] += 1
                else:
                    ut_dict[rvv] = {"count": 1}
    return ut_dict


def gen_cmd_rvismith(arg: dict):
    code_dir = os.path.join(tmp_dir, hash_arg(arg))
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

# return: coverage; CPU time
def one_rvismith(arg:dict):
    code_dir = os.path.join(tmp_dir, hash_arg(arg))
    os.mkdir(code_dir)

    cmd = gen_cmd_rvismith( arg )
    start = time.process_time() 
    result = subprocess.run([cmd], shell=True, capture_output=True, text=True ) # run rvismith
    end = time.process_time()
    
    code_path = os.path.join(code_dir, "allin.c")
    if( os.path.exists( code_path ) ):
        ut_dict = get_counts( [code_path] )
    else:
        print(f"rvismith fail: {hash_arg(arg)}")
        print(result.stderr)

    shutil.rmtree(code_dir)
    return ut_dict, end - start

def get_a_arg(_):
    seed, data_len, seq_len, root = getSeed(), 10, 10, getRoot()
    arg  = {'seed': [seed], 'data_length': [data_len], \
            'sequence_length': [seq_len], 'root': [root] }
    return arg

def rvismith_rvv_coverage():
    # parallel code
    args = []
    print("start generating args for rvismith...")
    with ProcessPoolExecutor() as executor:
        args = list( tqdm(executor.map(get_a_arg, [None] * code_number), total=code_number ) )
    csv_file = os.path.join(tmp_dir, "args.csv")
    dfs = pd.concat( (pd.DataFrame(item) for item in args), ignore_index=True)
    dfs.to_csv(csv_file, mode='w', header=False)
    print(f"args in: {csv_file}\n")

    print("start rvismith...")
    with ProcessPoolExecutor() as executor:
        res = list( tqdm(executor.map(one_rvismith, args), total=code_number ) ) # a list of dicts

    # merge
    merged_dict = init_dict
    time_gen = 0
    for d, cpu_time in res:
        for key, value in d.items():
            if( key in init_dict):
                merged_dict[key]["count"] += value["count"]
        time_gen += cpu_time

    merged_dict = dict(merged_dict)
    coverage, sum_count, sum_weight = api_coverage(merged_dict)
    print(f"rvismith rvv intrinsic coverage: {coverage * 100}%")
    print(f"covered: {sum_count}; total: {sum_weight}")
    print(f"generation CPU time: {time_gen}")
    json_file = os.path.join(tmp_dir, "cov.json")
    with open( json_file, "w" ) as fp:
        json.dump( merged_dict , fp, indent=4 )
    res_file = os.path.join(tmp_dir, "summary.json")
    with open( res_file , "w" ) as fp:
        res_dict = {"coverage": coverage, "count":sum_count, "total":sum_weight, "test_case_n": code_number, "cpu_time": time_gen }
        json.dump( res_dict , fp, indent=4 )
    print(f"result in: {res_file}")

if __name__ == "__main__":
    # set path
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', '--output_path', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "../"), help="output path of coverage results")
    parser.add_argument('-n', '--number', default=code_number, help="number of test cases")
    args = parser.parse_args()
    code_number = int(args.number) if int(args.number) > 0 else code_number
    tmp_dir = os.path.join(args.output_path, f"cov-rvismith-{code_number}-" + datetime.datetime.now().strftime('%Y%m%d-%H%M%S') )
    if( os.path.exists(tmp_dir) == False ): 
        os.mkdir( tmp_dir )

    set_gen_config(mode)
    init_dict = get_init_dict()
    rvismith_rvv_coverage()