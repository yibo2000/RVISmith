import os
import sys
import shutil
import subprocess
import argparse
from tqdm import tqdm
import random
import numpy as np
import json
import pandas as pd
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

# global vars
rvismith_path = ""
testcode_path = ""
number = 0
segment = False
policy = False
overloaded = False

def getSeed():
    #random_uint32 = np.random.randint(0, 2**32, dtype=np.uint32)
    #return hex(random_uint32)
    return f"0x{random.getrandbits(32):08x}"

def getDataLength():
    #data_length_distribution = [ (1, 1), (2, 10), (11, 50), (51, 100), (101, 500), (501, 1000), (1001, 5000), (5001, 10000) ]
    data_length_distribution = [ (1, 1), (2, 10), (11, 50), (51, 100), (101, 500), (501, 1000) ]
    minv, maxv = data_length_distribution[random.randint(0, len(data_length_distribution)-1)]
    return str(random.randint(minv, maxv))

def getSeqLength():
    seq_length_distribution = [ (1, 1), (2, 3), (4, 5), (6, 10), (11, 15), (16, 20), (21, 30), (31, 40), (41, 50), (51, 100) ]
    minv, maxv = seq_length_distribution[random.randint(0, len(seq_length_distribution)-1)]
    return str(random.randint(minv, maxv))

def getRoot():
    
    vint_type = ['vint64m1_t', 'vint64m2_t', 'vint64m4_t', 'vint64m8_t'] \
    + ['vint32m1_t', 'vint32m2_t', 'vint32m4_t', 'vint32m8_t', 'vint32mf2_t'] \
    + ['vint16m1_t', 'vint16m2_t', 'vint16m4_t', 'vint16m8_t', 'vint16mf2_t', 'vint16mf4_t'] \
    + ['vint8m1_t', 'vint8m2_t', 'vint8m4_t', 'vint8m8_t', 'vint8mf2_t', 'vint8mf4_t', 'vint8mf8_t']
    
    vuint_type = ['vuint64m1_t', 'vuint64m2_t', 'vuint64m4_t', 'vuint64m8_t'] \
    + ['vuint32m1_t', 'vuint32m2_t', 'vuint32m4_t', 'vuint32m8_t', 'vuint32mf2_t'] \
    + ['vuint16m1_t', 'vuint16m2_t', 'vuint16m4_t', 'vuint16m8_t', 'vuint16mf2_t', 'vuint16mf4_t'] \
    + ['vuint8m1_t', 'vuint8m2_t', 'vuint8m4_t', 'vuint8m8_t', 'vuint8mf2_t', 'vuint8mf4_t' ,'vuint8mf8_t']

    vfloat_type = ['vfloat64m1_t', 'vfloat64m2_t', 'vfloat64m4_t', 'vfloat64m8_t'] \
    + ['vfloat32m1_t', 'vfloat32m2_t', 'vfloat32m4_t', 'vfloat32m8_t', 'vfloat32mf2_t'] \
    + ['vfloat16m1_t', 'vfloat16m2_t', 'vfloat16m4_t', 'vfloat16m8_t', 'vfloat16mf2_t', 'vfloat16mf4_t'] \
    
    vbool_type = ['vbool1_t', 'vbool2_t', 'vbool4_t', 'vbool8_t', 'vbool16_t', 'vbool32_t', 'vbool64_t']

    types = vint_type + vuint_type + vfloat_type + vbool_type
    return random.choice(types)


def once_gen(n):
    code_dir = os.path.join(testcode_path, "code", str(n))
    if( os.path.exists(code_dir) == False ): os.mkdir( code_dir )
    else:
        shutil.rmtree( code_dir )
        os.mkdir( code_dir )

    # generate test code
    cmd = rvismith_path
    if(segment): cmd += " --segment "
    if(policy): cmd += " --policy "
    if(overloaded): cmd += " --overloaded "
    seed, data_len, seq_len, root = getSeed(), getDataLength(), getSeqLength(), getRoot()
    cmd += " --seed " + seed \
        + " --data_length " + data_len \
        + " --sequence_length " + seq_len \
        + " --root " + root \
        + " -o " + os.path.join(code_dir)

    result = subprocess.run([cmd], shell=True, capture_output=True, text=True )

    if (result.stderr.strip() != ""):
        logf = open(os.path.join(code_dir, "rvismith.log"), "w", encoding="utf-8" )
        logf.write(cmd + "\n")
        logf.write(result.stdout)
        logf.write(result.stderr)
        logf.close()

    data = {'id': [str(n)], 'seed': [seed], 'data_length': [data_len], 'sequence_length': [seq_len], 'root': [root] }
    return data


# generate cases n times
def gen_test_cases(N: int = 10):
    # N: max test code number
    if( N < 0 ): N = 10
    print("Start generating test cases...")
    tasks = list(range(int(N)))
    data = []
    with ProcessPoolExecutor() as executor:
        data = list( tqdm(executor.map(once_gen, tasks), total=N ) )
    
    csv_file = os.path.join(testcode_path, "args.csv")
    if( os.path.exists(csv_file) == True ): os.remove( csv_file )
    dfs = [ pd.DataFrame(item) for item in data ]
    combined_df = pd.concat(dfs, ignore_index=True)
    combined_df.to_csv(csv_file, mode='w', header=False, index=False)
    return 0


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-r', '--rvismith_path', required=True, help="path to rvismith")
    parser.add_argument('-o', '--testcode_path', required=True, help="output path of test cases")
    parser.add_argument('-n', '--number', default=10, help="test case number")
    parser.add_argument('--segment', action="store_true", help="whether segment load-store intrinsics included")
    parser.add_argument('--policy', action="store_true", help="whether load-store intrinsics with policy suffixes included")
    parser.add_argument('--overloaded', action="store_true", help="whether overloaded load-store intrinsics included")
    
    args = parser.parse_args()
    if (not args.rvismith_path) or (os.path.exists(args.rvismith_path) == False):
        print('please check the path of rvismith.', file = sys.stderr)
        sys.exit(1)
    if (os.path.exists(args.testcode_path) == False):
        os.mkdir( args.testcode_path )
    if( os.path.exists(os.path.join(args.testcode_path, "code")) == False ): 
        os.mkdir( os.path.join(args.testcode_path, "code") )
    else:
        if( len(os.listdir( os.path.join(args.testcode_path, "code") )) !=0 ):
            # is not empty directory
            print('code dir in test code path is not empty.', file = sys.stderr)
            exit(1)

    rvismith_path = args.rvismith_path
    testcode_path = args.testcode_path
    number = int(args.number) if int(args.number) > 0 else 10
    segment = args.segment
    policy = args.policy
    overloaded = args.overloaded

    with open( os.path.join(args.testcode_path, "gen_config.json"), "w", encoding="utf-8") as json_file:
        data = {"rvismith_path": args.rvismith_path, \
                "testcode_path": args.testcode_path, \
                "number": number, \
                "segment": 1 if segment else 0, \
                "policy": 1 if policy else 0, \
                "overloaded": 1 if overloaded else 0
                }
        cf = json.dump(data, json_file, indent=4 )

    gen_test_cases(number)
