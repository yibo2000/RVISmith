import os
import sys
import time
from tqdm import tqdm
import datetime
import subprocess
import shutil
import argparse
import json
from concurrent.futures import ProcessPoolExecutor
NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
from RVISmithDriver import hash_arg, get_a_arg

rvismith_path = "/home/RVISmith-1.0.0-ubuntu-24.04-x86_64/bin/rvismith"
config = {
    "gcc-O0":{
        "compiler": "/home/compiler/gcc/14.2.0/bin/gcc -march=rv64gcv_zvfh -mabi=lp64d -Wno-psabi -static -O0 ",
        "emulator": "/home/emulator/qemu-9.1.0/build/qemu-riscv64"
    }, 
    "gcc-O3":{
        "compiler": "/home/compiler/gcc/14.2.0/bin/gcc -march=rv64gcv_zvfh -mabi=lp64d -Wno-psabi -static -O3 ",
        "emulator": "/home/emulator/qemu-9.1.0/build/qemu-riscv64"
    },
    "clang-O0":{
        "compiler": "/home/compiler/llvm/19.1.4/bin/clang -march=rv64gcv_zvfh -mabi=lp64d -Wno-psabi -static -O0 ",
        "emulator": "/home/emulator/qemu-9.1.0/build/qemu-riscv64"
    }, 
    "clang-O3":{
        "compiler": "/home/compiler/llvm/19.1.4/bin/clang -march=rv64gcv_zvfh -mabi=lp64d -Wno-psabi -static -O3 ",
        "emulator": "/home/emulator/qemu-9.1.0/build/qemu-riscv64"
    }
}
output_path = ""
dt = ""
total_number = 10

def get_time():
    return time.process_time() # CPU time
    #return time.time()

def get_init_dict():
    res = {}
    res["rvismith"] = 0
    for key in config.keys():
        res[key] = {}
        res[key]["compilation"] = 0
        res[key]["execution"] = 0
    return res
init_dict = get_init_dict()

def one_test(_):
    res = init_dict
    arg = get_a_arg(None)
    code_dir = os.path.join(output_path, dt, hash_arg(arg))
    os.mkdir(code_dir)

    # code generation by RVISmith
    rvismith_cmd = rvismith_path + " --segment "\
        + f" --seed {arg['seed'][0]}"\
        + f" --data_length {arg['data_length'][0]}"\
        + f" --sequence_length {arg['sequence_length'][0]}"\
        + f" --root {arg['root'][0]}"\
        + f" --output {code_dir}"
    
    start = get_time()
    result = subprocess.run([rvismith_cmd], shell=True, capture_output=True, text=True ) # run rvismith
    end = get_time()
    res["rvismith"] = end - start

    # compilation and execution
    for key in config.keys():
        for case in ["allin.c", "unit.c", "random.c"]:
            c_cmd = config[key]["compiler"] + os.path.join(code_dir, case) + \
                    f" -o {os.path.join(code_dir, case.replace('.c', '.out'))}"
            e_cmd = config[key]["emulator"] + os.path.join(code_dir, case.replace('.c', '.out'))

            start = get_time()
            result = subprocess.run([c_cmd], shell=True, capture_output=True, text=True )
            end = get_time()
            res[key]["compilation"] += end-start

            start = get_time()
            result = subprocess.run([e_cmd], shell=True, capture_output=True, text=True )
            end = get_time()
            res[key]["execution"] += end-start

    shutil.rmtree(code_dir)
    return res

def rvismith_performance_parallel():
    with ProcessPoolExecutor() as executor:
        res_total = list( tqdm(executor.map(one_test, [None] * total_number), total=total_number ) )
    
    merged_dict = init_dict
    for res in res_total:
        merged_dict["rvismith"] += res["rvismith"]
        for key in config.keys():
            merged_dict[key]["compilation"] += res[key]["compilation"]
            merged_dict[key]["execution"] += res[key]["execution"]
    
    merged_dict = print_result(merged_dict)
    return merged_dict
    
def print_result(res:dict):
    total_time = res["rvismith"]
    for key in config.keys():
        total_time += res[key]["compilation"]
        total_time += res[key]["execution"]
    # print
    res["performance"] = {}
    res["performance"]["total"] = f'{total_time:.3f}s'
    res["performance"]["rvismith"] = f'{res["rvismith"]/total_time*100:.3f}%'
    for key in config.keys():
        res["performance"][key] = {}
        res["performance"][key]["compilation"] = f'{res[key]["compilation"]/total_time*100:.3f}%'
        res["performance"][key]["execution"] = f'{res[key]["execution"]/total_time*100:.3f}%'
    print(json.dumps( res, indent=4 ))
    return res

if __name__ == "__main__":
    output_path = "./"
    dt = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
    os.mkdir( os.path.join(output_path, dt) )
    init_dict = get_init_dict()

    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--number', default=total_number, help="number of test cases")
    args = parser.parse_args()
    total_number = int(args.number) if int(args.number) > 0 else total_number

    res = rvismith_performance_parallel()
    json_file = os.path.join(output_path, dt, "performance.json")
    with open( json_file, "w" ) as fp:
        json.dump( res , fp, indent=4 )
