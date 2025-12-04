import os
import sys
import subprocess
from enum import Enum, auto

sys.path = [os.path.abspath( os.path.dirname(os.path.abspath(__file__))  )] + sys.path
from Config import Config

testcode_path = ""
eval_result_path = ""
config_path = ""

class TestResult(Enum):
    Pass = auto()
    FuzzerFail = auto()
    CompilerCrash = auto()
    RuntimeCrash = auto()
    DiffChecksum = auto()
    Timeout = auto()

def oneEval(config:Config, code_dir:str):
    # init
    assert(os.path.exists( os.path.join(code_dir, f"test.cpp") ))

    stdout = []
    compile_run_success = []
    # compile and run
    out_path = os.path.join(code_dir, "a.out")
    for i in range(0, len( config.compiler_paths)):
        # compile
        cmd_compile = f"{config.compiler_paths[i]} {config.compiler_flags[i]} {os.path.join(code_dir, f"test.cpp")} -o {out_path}"
        
        try:
            result_compile = subprocess.run([x for x in cmd_compile.split(" ") if x], check=True, capture_output=True, text=True, timeout=10)
        except subprocess.TimeoutExpired: # timeout
            return TestResult.Timeout, f"{cmd_compile}"
        except subprocess.CalledProcessError as e:
            return TestResult.CompilerCrash, f"{e.stderr}: {cmd_compile}"
        
        # run
        cmd_run = f"{config.sim_path} {config.sim_flag} {out_path}" # if emulator needs flags, fix this line
        
        try:
            result_run = subprocess.run([x for x in cmd_run.split(" ") if x], check=True, capture_output=True, text=True, timeout=10)
        except subprocess.TimeoutExpired: # timeout
            return TestResult.Timeout, f"{cmd_run}"
        except subprocess.CalledProcessError as e:
            return TestResult.RuntimeCrash, f"{e.stderr}: {cmd_run}"

        stdout.append(result_run.stdout.strip())
        compile_run_success.append(i)
    
    if(os.path.exists(out_path)): os.remove(out_path)

    # differential testing
    assert( len(stdout) == len(compile_run_success) )
    length = len(compile_run_success)
    if(length >= 2):
        for i in range(0, length):
            for j in range(i+1, length):
                different = (stdout[i] != stdout[j])
                if(different == True):
                    logtext = f"{i} and {j}, calculation error.\n"
                    logtext += f"{i}: {config.compiler_paths[i]} {config.compiler_flags[i]}\n{stdout[i]}\n"
                    logtext += f"{j}: {config.compiler_paths[j]} {config.compiler_flags[j]}\n{stdout[j]}\n"
                    return TestResult.DiffChecksum, logtext
    
    return TestResult.Pass, ""
