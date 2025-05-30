import os
import sys
import argparse

NOWPATH = os.path.dirname(os.path.abspath(__file__))
#version_llvm = ["17.0.1", "17.0.6", "18.1.0", "18.1.8", "19.1.0", "19.1.4", "20-init", "20-trunk"]
#finish: 17.0.1, 18.1.8, 19.1.0
version_llvm = ["17.0.6", "18.1.0", "18.1.8", "19.1.0", "19.1.4", "20-init", "20-trunk"]
version_gcc = ["14-20240107", "14-20241116", "14.1.0", "14.2.0", "15-20240428", "15-20241117"]
output_path = ""
number = 0

# preparation
def preparation():
    for ver in version_gcc:
        config_path = f"/home/configs/qemu/config_gcc_{ver}.txt"
        compiler_path = f"/home/compiler/gcc/{ver}/bin/gcc"
        assert( os.path.exists(config_path) )
        assert( os.path.exists(compiler_path) )
    for ver in version_llvm:
        config_path = f"/home/configs/qemu/config_llvm_{ver}.txt"
        compiler_path = f"/home/compiler/llvm/{ver}/bin/clang"
        assert( os.path.exists(config_path) )
        assert( os.path.exists(compiler_path) )

def test_gcc():
    for ver in version_gcc:
        config_path = f"/home/configs/qemu/config_gcc_{ver}.txt"
        res_path = os.path.join(output_path, "gcc-"+ver)
        if(os.path.exists(res_path) == False): os.mkdir(res_path)
        print(f"test gcc {ver}...")
        cmd = f"python3 {os.path.join(NOWPATH, "RVISmithDriver.py") } \
                -r /home/RVISmith-1.0.0-ubuntu-24.04-x86_64/bin/rvismith \
                -c {config_path} \
                -n {number} \
                -o {res_path}"
        os.system( cmd )

def test_llvm():
    for ver in version_llvm:
        config_path = f"/home/configs/qemu/config_llvm_{ver}.txt"
        res_path = os.path.join(output_path, "llvm-"+ver)
        if(os.path.exists(res_path) == False): os.mkdir(res_path)
        print(f"test llvm {ver}...")
        cmd = f"python3 {os.path.join(NOWPATH, "RVISmithDriver.py") } \
                -r /home/RVISmith-1.0.0-ubuntu-24.04-x86_64/bin/rvismith \
                -c {config_path} \
                -n {number} \
                -o {res_path}"
        os.system( cmd )

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--number', default=10, help="test case number")
    parser.add_argument('-o', '--output_path', required=True, help="output path of test cases")
    args = parser.parse_args()
    number = int(args.number) if int(args.number) > 0 else 10
    if (os.path.exists(args.output_path) == False):
        os.mkdir(args.output_path)
    output_path = os.path.abspath(args.output_path)
    preparation()
    test_llvm()
    test_gcc()