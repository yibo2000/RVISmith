# intrinsic coverage script for RIF
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
import random
import time
NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
import OpDefParser
from RVISmithCoverage import hash_arg
from TestGen import getSeed
assert sys.version_info >= (3, 10)

rif_random_path = "/home/RIF/build/tool/random_gen" # path to random_gen
rif_fused_path = "/home/RIF/build/tool/fused_gen" # path to fused_gen
rif_opdef_path = "/home/RIF/include/CustomOperator.def" # path to `CustomOperator.def` used by RIF, for generating root arguments
code_number = 500
tmp_dir = ""

from RVISmithCoverage import set_gen_config
mode = 0
set_gen_config(mode)
from RVISmithCoverage import under_test_list_file, policy
from RVISmithCoverage import get_counts, api_coverage, get_init_dict
init_dict = {}

# operators in rif
policy_attrs = ["TailAgnostic", "TailUndisturbed", "MaskAgnostic", "MaskUndisturbed"]
op_no_policy = []
op_policy = []
def read_rif_def():
    with open( rif_opdef_path, "r", encoding="utf-8" ) as fp:
        for line in fp:
            if(line.strip()=="" or line.startswith("//")): continue
            op_info = OpDefParser.parse_line(line)
            if(op_info == None):
                # print(line)
                continue
            has_policy = False
            for att in policy_attrs:
                if(att in op_info.op_attr): has_policy = True
            if(has_policy): op_policy.append(op_info.op_type)
            else: op_no_policy.append(op_info.op_type)
    print(f"len op_no_policy: {len(op_no_policy)}")
    print(f"len op_policy: {len(op_policy)}")

def get_rif_root():
    if(policy): return random.choice(op_policy)
    else: return random.choice(op_no_policy)

def get_a_arg(_):
    seed, data_len, seq_len, root = getSeed(), 10, 10, get_rif_root()
    arg  = {'seed': [seed], 'data_length': [data_len], \
            'sequence_length': [seq_len], 'root': [root] }
    return arg

def gen_cmd_rif(arg: dict):
    code_dir = os.path.join(tmp_dir, hash_arg(arg))
    cmd_args = " "
    cmd_args += f" --seed={arg['seed'][0]} "\
        + f" --length={arg['data_length'][0]} "\
        + f" --nodes-to-gen={arg['sequence_length'][0]} "\
        + f" --dot={os.path.join(code_dir, 'output.dot')} "\
        + f" --root {arg['root'][0]} "
    if(policy): cmd_args += " --has-policy --has-ta --has-ma "
    # one cmd for random_gen, one cmd for fused_gen
    return  rif_random_path+cmd_args+ f" --code={os.path.join(code_dir, 'random.c')} ", \
            rif_fused_path+cmd_args+ f" --code={os.path.join(code_dir, 'fused.c')} "

def one_rif(arg:dict):
    code_dir = os.path.join(tmp_dir, hash_arg(arg))
    os.mkdir(code_dir)

    cmd_random, cmd_fused = gen_cmd_rif( arg )
    code_path = []
    # run random rif
    start = time.process_time() 
    result = subprocess.run([cmd_random], shell=True, capture_output=True, text=True )
    end = time.process_time()
    random_cpu_time = end - start
    p1 = os.path.join(code_dir, "random.c")
    if( p1 ): code_path.append(p1)
    else:
        pass
        #print(f"rif fail: {hash_arg(arg)}")
        #print(result.stderr)
    # run fused rif
    start = time.process_time() 
    result = subprocess.run([cmd_fused], shell=True, capture_output=True, text=True )
    end = time.process_time()
    fused_cpu_time = end - start
    p2 = os.path.join(code_dir, "fused.c")
    if( p2 ): code_path.append(p2)

    ut_dict = get_counts( code_path )
    shutil.rmtree(code_dir)
    return ut_dict, random_cpu_time, fused_cpu_time


def rif_rvv_coverage():
    # parallel code
    args = []
    print("start generating args for rif...")
    with ProcessPoolExecutor() as executor:
        args = list( tqdm(executor.map(get_a_arg, [None] * code_number), total=code_number ) )
    csv_file = os.path.join(tmp_dir, "args.csv")
    dfs = pd.concat( (pd.DataFrame(item) for item in args), ignore_index=True)
    dfs.to_csv(csv_file, mode='w', header=False)
    print(f"args in: {csv_file}\n")

    print("start rif...")
    with ProcessPoolExecutor() as executor:
        res = list( tqdm(executor.map(one_rif, args), total=code_number ) ) # a list of dicts

    # merge
    merged_dict = init_dict
    random_time_gen, fused_time_gen = 0, 0
    for d, rtime, ftime in res:
        for key, value in d.items():
            if( key in init_dict):
                merged_dict[key]["count"] += value["count"]
        random_time_gen += rtime
        fused_time_gen += ftime

    merged_dict = dict(merged_dict)
    coverage, sum_count, sum_weight = api_coverage(merged_dict)
    print(f"rif rvv intrinsic coverage: {coverage * 100}%")
    print(f"covered: {sum_count}; total: {sum_weight}")
    print(f"random_gen CPU time: {random_time_gen}")
    print(f"fused_gen CPU time: {fused_time_gen}")
    json_file = os.path.join(tmp_dir, "cov.json")
    with open( json_file, "w" ) as fp:
        json.dump( merged_dict , fp, indent=4 )
    res_file = os.path.join(tmp_dir, "summary.json")
    with open( res_file , "w" ) as fp:
        res_dict = {"coverage": coverage, "count":sum_count, "total":sum_weight, "test_case_n": code_number, \
                    "cpu_time_random": random_time_gen, "cpu_time_fused": fused_time_gen}
        json.dump( res_dict , fp, indent=4 )
    print(f"result in: {res_file}")


if __name__ == "__main__":
    # set path
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', '--output_path', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "../"), help="output path of coverage results")
    parser.add_argument('-n', '--number', default=code_number, help="number of test cases")
    args = parser.parse_args()
    code_number = int(args.number) if int(args.number) > 0 else code_number
    tmp_dir = os.path.join(args.output_path, f"cov-rif-{code_number}-" + datetime.datetime.now().strftime('%Y%m%d-%H%M%S') )
    if( os.path.exists(tmp_dir) == False ): 
        os.mkdir( tmp_dir )
        
    set_gen_config(mode)
    read_rif_def()
    init_dict = get_init_dict()
    rif_rvv_coverage()