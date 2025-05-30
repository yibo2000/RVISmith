## CCS25-Artifact-RVISmith

### 1-Prerequisites

Available at: https://zenodo.org/records/15548270

The full evaluation of this artifact is resource-intensive. We recommend to run the full evaluation on a machine with at least **32 cores, 32GB memory, and 50GB disk space** to achieve a reasonable evaluation time.

### 2-Getting Started Guide

First, download the artifact from the provided Zenodo link , then untar the artifact:

```bash
$ tar -xzf ccs25-artifact-rvismith.tar.gz # 2~5 minutes
```

Then, enter the docker container:

```bash
$ cd /path/to/ccs25-artifact-rvismith
$ docker load -i image-ccs25-artifact-rvismith.tar.gz # 3~5 minutes
$ docker run -it image-ccs25-artifact-rvismith
```

Docker Image Layout:

| Container Folder              | Content                                                      |
| ----------------------------- | ------------------------------------------------------------ |
| `/artifact-ccs25/rvismith`    | Fuzzer executables of RVISmith (in `bin`) and the differential testing framework (in `scripts`) |
| `/artifact-ccs25/compiler-rv` | Compiler executables (to be tested) that compile source code to riscv64 instructions |
| `/artifact-ccs25/qemu-9.1.0`  | Emulator executables for executing compiled riscv executables |
| `/artifact-ccs25/rif`         | The baseline executables developed by SiFive ([link](https://github.com/sifive/riscv-vector-intrinsic-fuzzing)) |
| `/artifact-ccs25/results`     | Code coverage results                                        |

Check the tools inside the docker container:

```bash
# in the container
# check gcc (version: 15.0.0 20240428)
$ /artifact-ccs25/compiler-rv/bin/riscv64-unknown-elf-gcc --version
# check clang (version: 19.1.4)
$ /artifact-ccs25/compiler-rv/bin/riscv64-unknown-elf-clang --version
# check qemu for riscv64 (version: 9.1.0)
$ /artifact-ccs25/qemu-9.1.0/build/qemu-riscv64 --version
# check rvismith binary
$ /artifact-ccs25/rvismith/bin/rvismith -h
```

### 3-Quickstart

Generate a code example by RVISmith, then compile and execute the program:

```bash
$ cd /artifact-ccs25/rvismith/bin
$ ./rvismith
$ /artifact-ccs25/compiler-rv/bin/riscv64-unknown-elf-gcc allin.c -march=rv64gcv_zvfh -mabi=lp64d -static -O3 -o ./allin.out
# or use clang for compilation
# /artifact-ccs25/compiler-rv/bin/clang allin.c -march=rv64gcv_zvfh -mabi=lp64d -static -O3 -o ./allin.out
$ /artifact-ccs25/qemu-9.1.0/build/qemu-riscv64 ./allin.out
```

RVISmith generates three programs: `allin.c`, `random.c`, and `unit.c`. Operations in the three programs are the same (i.e., they are equivalent programs), and the only difference is the intrinsic scheduling mode used to insert load/store intrinsics (see Section 3.3 in our paper).

If everything works correctly, the element values after operations will be printed on the screen; otherwise, you may have encountered a compiler bug.

More arguments:

```bash
$ ./rvismith -h
One line description of RVISmith
Usage:
  rvismith [OPTION...]

  -s, --seed arg             Seed (default: 0xdeadbeef)
  -l, --data_length arg      Data length (default: 10)
  -n, --sequence_length arg  Sequence length (default: 10)
  -r, --root arg             Root (connect vector type) (default: vint8mf8_t)
  -o, --output arg           Output path (default: ./)
      --segment              Whether segment load-store intrinsics are 
                             included (default: false)
      --policy               Whether load-store intrinsics with policy 
                             suffixes are included (default: false)
      --overloaded           Whether overloaded load-store intrinsics are 
                             included (default: false)
  -h, --help                 Print usage
```

We provide multiple RVISmith executables, each built from different portions of the intrinsic documents (as we discussed in Section 3.1 in our paper:

```bash
$ ls /artifact-ccs25/rvismith/bin
```

| Target intrinsic                                     | Executable                  | Flag                                  |
| ---------------------------------------------------- | --------------------------- | ------------------------------------- |
| explicit (non-overloaded) intrinsics                 | rvismith, rvismith-explicit | --segment                             |
| explicit (non-overloaded) intrinsics policy variants | rvismith-explicit-policy    | --segment --policy                    |
| implicit (overloaded) intrinsics                     | rvismith-implicit           | --segment --overloaded                |
| implicit (overloaded) intrinsics policy variants     | rvismith-implicit-policy    | --segment --policy --overloaded       |
| all                                                  | rvismith-all                | [--segment] [--policy] [--overloaded] |

### 4-Step-by-step instructions (Reusable + Reproducible)

#### (Section 4.2) Quantitative bug-finding results

There are two recommended approaches to reuse RVISmith:

- using the driver `RVISmithDriver.py`: generating programs + differential testing (only bug-triggering cases are kept)
- using `TestGen.py`: generating programs (for further usage)

##### Reuse `RVISmithDriver.py`

The default configuration of differential testing:

```bash
$ cat /artifact-ccs25/rvismith/config/config.txt
```

The default configuration is comparing results between `gcc -O0`, `gcc -O3`, `clang -O0`, and `clang -O3`. You can change the configuration as you want. As the configuration template in `/artifact-ccs25/rvismith/scripts/config_example.txt`:

- line1: path to the emulator for riscv64

- line2: emulator flags

- line3-n: compiler paths and flags

The driver generates programs with **n** random seeds, differential fuzzing compilers using the given configuration, and record testing results and bug-triggering cases. The above steps run in parallel.

For example, generating 300 programs when $n=100$ (100 random seeds * 3 scheduling modes):

```bash
$ export RVISMITH_PATH="/artifact-ccs25/rvismith/bin/rvismith"
$ export CONFIG_PATH="/artifact-ccs25/rvismith/config/config.txt"
$ cd /artifact-ccs25/rvismith/scripts/
$ python3 RVISmithDriver.py -n 100 -r $RVISMITH_PATH -c $CONFIG_PATH 
$ ls ./rvismith_eval/[datetime]
```

Evaluation results will be saved in the directory `./rvismith_eval/(datetime)`:

| File/Folder       | Content                                                      |
| ----------------- | ------------------------------------------------------------ |
| `args.csv`        | used arguments by RVISmith: (id, seed, data_length, sequence_length, root) |
| `diff.log`        | detected potential bug-triggering cases and results (dir, allin_res, random_res, unit_res, emi_res) |
| `emi.log`         | detected potential bug-triggering cases by EMI checking (typically a subset of `diff.log`) |
| `error_log`       | error messages when compilation and execution                |
| `gen_config.json` | the recorded arguments of this differential testing          |
| `res.csv`         | complete results                                             |
| `tmp`             | potential bug-triggering cases                               |

Getting a summary for this time of differential testing (how we get the data in Figure 6 in our paper):

```bash
$ cd /artifact-ccs25/rvismith/scripts/
$ python3 Summary.py ./rvismith_eval/(datetime)/res.csv
```

##### Reuse `TestGen.py`

The driver removes the passed test cases and keeps only potential bug-triggering cases in `./rvismith_eval/(datetime)/tmp` to reduce the disk space consumption. If you want to generate programs for further usage, you can use `TestGen.py` to generate **n** programs without evaluation:

```bash
$ mkdir [output_path]
$ python3 TestGen.py -n 100 -r $RVISMITH_PATH -o [output_path]
```

##### Reproduce the main results of Section 4.2

[Table 3: new bugs] We provide our detected minimum bug cases, along with detailed descriptions, `/artifact-ccs25/rvismith/reported-bugs/`. Some of the bugs may not be present in the versions of the compilers provided in our artifact.

```bash
$ ls /artifact-ccs25/rvismith/reported-bugs/
```

[Figure 6: quantitative results] Using the driver as discussed above:

```bash
# gcc-15-20240428: around 7-8 hours using 256 cpu cores
$ export RVISMITH_PATH="/artifact-ccs25/rvismith/bin/rvismith"
$ export CONFIG_PATH="/artifact-ccs25/rvismith/config/config-gcc-15-20240428.txt"
$ cd /artifact-ccs25/rvismith/scripts/
$ python3 RVISmithDriver.py -n 500000 -r $RVISMITH_PATH -c $CONFIG_PATH -o ./gcc-15
$ python3 Summary.py ./gcc-15/(datetime)/res.csv

# llvm-19.1.4: around 6-7 hours using 256 cpu cores
$ export CONFIG_PATH="/artifact-ccs25/rvismith/config/config-llvm-19.1.4.txt"
$ cd /artifact-ccs25/rvismith/scripts/
$ python3 RVISmithDriver.py -n 500000 -r $RVISMITH_PATH -c $CONFIG_PATH -o ./llvm-19
$ python3 Summary.py ./llvm-19/(datetime)/res.csv
```

To reproduce the results in Figure 6 on other versions of compilers, you need to build the cross-compiler from source (see [riscv-gnu-compiler-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)). Reproducing all the results shown in Figure 6 takes about two weeks (not recommended).

#### (Section 4.3) Coverage

##### Reuse the intrinsic coverage script

Use `RVISmithCoverage.py` for evaluation on intrinsic coverage of RVISmith. **Set appropriate `rvismith_path` and `mode` in `RVISmithCoverage.py`** before using the script (dufault: explicit intrinsics):

| Intrinsic                                            | RVISmith                 | Mode |
| ---------------------------------------------------- | ------------------------ | ---- |
| explicit (non-overloaded) intrinsics                 | rvismith-explicit        | 0    |
| explicit (non-overloaded) intrinsics policy variants | rvismith-explicit-policy | 1    |
| implicit (overloaded) intrinsics                     | rvismith-implicit        | 2    |
| implicit (overloaded) intrinsics policy variants     | rvismith-implicit-policy | 3    |

```bash
$ cd /artifact-ccs25/rvismith/scripts/
# setting `mode` and `rvismith_path` in `RVISmithCoverage.py` before using if you want to change the intrinsics under test (default: explicit intrinsics)
# vim RVISmithCoverage.py
$ python3 RVISmithCoverage.py -n 1000 -o ./
```

Intrinsic coverage results will be placed in `./cov-rvismith-[n]-[datetime]/summary.json`

```bash
$ cat ./cov-rvismith-[n]-[datetime]/summary.json
```

For the baseline RIF, the way to get intrinsic coverage is similar. Code generator of RIF is placed in `/artifact-ccs25/rif/tool/`:

```bash
$ /artifact-ccs25/rif/tool/random_gen -h
$ /artifact-ccs25/rif/tool/fused_gen -h
```

Use the script `RIFCoverage.py`:

```bash
$ cd /artifact-ccs25/rvismith/scripts/
# setting `mode` in `RIFCoverage.py` before using if you want to change the intrinsics under test, dufault: explicit intrinsics
# vim RIFCoverage.py
$ python3 RIFCoverage.py -n 1000 -o ./
$ cat ./cov-rif-[n]-[datetime]/summary.json
```

##### Reproduce the main results of Section 4.3

[Table 5: code coverage]

We use `gcov` for GCC code coverage collection and `llvm-cov` for LLVM code coverage collection.

To get compiler source code coverage, several options are required to insert instrumentation that records which lines are executed when building the [riscv-gnu-compiler-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) from source code.

For GCC:

```
CFLAGS="-g -ftest-coverage -fprofile-arcs" \
CXXFLAGS="-g -ftest-coverage -fprofile-arcs" \
LDFLAGS="-lgcov --coverage" \
CFLAGS_FOR_TARGET="-Os $(CFLAGS_FOR_TARGET)" \
CXXFLAGS_FOR_TARGET="-Os $(CXXFLAGS_FOR_TARGET)"
```

For LLVM:

```
-DCMAKE_C_COMPILER=/usr/bin/clang \
-DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
-DLLVM_BUILD_INSTRUMENTED_COVERAGE=On
```

[Not recommended] We do not recommend reproducing this result from source code.Compilers constructed in this manner require considerable time and disk space, and the use of `gcov` and `lcov` is very cumbersome. 

[Recommended] We present the code coverage results in this artifact in `/artifact-ccs25/results/code-coverage/gcc` and `/artifact-ccs25/results/code-coverage/llvm`. Check the results:

```bash
$ ls /artifact-ccs25/results/code-coverage/gcc
$ ls /artifact-ccs25/results/code-coverage/llvm
$ lynx /artifact-ccs25/results/code-coverage/gcc/cov_[generator]/index.html
$ lynx /artifact-ccs25/results/code-coverage/llvm/cov_[generator]/clang/summary.txt
```

[Table 6: Intrinsic coverage]

RVISmith (around 2 hours):

```bash
# Explicit intrinsics
# vim RVISmithCoverage.py
# rvismith_path = "/artifact-ccs25/rvismith/bin/rvismith"
# mode = 0
$ python3 RVISmithCoverage.py -n 100 -o ./
$ python3 RVISmithCoverage.py -n 1000 -o ./
$ python3 RVISmithCoverage.py -n 10000 -o ./
$ python3 RVISmithCoverage.py -n 100000 -o ./

# Explicit intrinsics, policy variants
# vim RVISmithCoverage.py
# rvismith_path = "/artifact-ccs25/rvismith/bin/rvismith-explicit-policy"
# mode = 1
$ python3 RVISmithCoverage.py -n 100 -o ./
$ python3 RVISmithCoverage.py -n 1000 -o ./
$ python3 RVISmithCoverage.py -n 10000 -o ./
$ python3 RVISmithCoverage.py -n 100000 -o ./

# Implicit intrinsics
# vim RVISmithCoverage.py
# rvismith_path = "/artifact-ccs25/rvismith/bin/rvismith-implicit"
# mode = 2
$ python3 RVISmithCoverage.py -n 100 -o ./
$ python3 RVISmithCoverage.py -n 1000 -o ./
$ python3 RVISmithCoverage.py -n 10000 -o ./
$ python3 RVISmithCoverage.py -n 100000 -o ./

# Implicit intrinsics, policy variants
# vim RVISmithCoverage.py
# rvismith_path = "/artifact-ccs25/rvismith/bin/rvismith-implicit-policy"
# mode = 3
$ python3 RVISmithCoverage.py -n 100 -o ./
$ python3 RVISmithCoverage.py -n 1000 -o ./
$ python3 RVISmithCoverage.py -n 10000 -o ./
$ python3 RVISmithCoverage.py -n 100000 -o ./
```

RIF (around 2 hours):

```bash
# Explicit intrinsics
# vim RIFCoverage.py
# mode = 0
$ python3 RIFCoverage.py -n 100 -o ./
$ python3 RIFCoverage.py -n 1000 -o ./
$ python3 RIFCoverage.py -n 10000 -o ./
$ python3 RIFCoverage.py -n 100000 -o ./

# Explicit intrinsics, policy variants
# vim RIFCoverage.py
# mode = 1
$ python3 RIFCoverage.py -n 100 -o ./
$ python3 RIFCoverage.py -n 1000 -o ./
$ python3 RIFCoverage.py -n 10000 -o ./
$ python3 RIFCoverage.py -n 100000 -o ./

# Implicit intrinsics
# vim RIFCoverage.py
# mode = 2
$ python3 RIFCoverage.py -n 100 -o ./
$ python3 RIFCoverage.py -n 1000 -o ./
$ python3 RIFCoverage.py -n 10000 -o ./
$ python3 RIFCoverage.py -n 100000 -o ./

# Implicit intrinsics, policy variants
# vim RIFCoverage.py
# mode = 3
$ python3 RIFCoverage.py -n 100 -o ./
$ python3 RIFCoverage.py -n 1000 -o ./
$ python3 RIFCoverage.py -n 10000 -o ./
$ python3 RIFCoverage.py -n 100000 -o ./
```

[Figure 7: distribution]

```bash
$ cd /artifact-ccs25/rvismith/scripts
$ python3 cov_distribution.py
# 00: load-store
# 01: seg-load-store
# 02: integer
# 03: fixed-point
# 04: floating-point
# 05: reduction
# 06: mask
# 07: permutation
# 08: utility
```

#### (Section 4.4) Performance

##### Reuse the performance script

Choose whether to evaluate CPU time or real time in `Performance.py`:

```python
def get_time():
    return time.process_time() # CPU Time
    #return time.time() # Real Time
```

##### Reproduce the main results of Section 4.4

Reproduce the results in Table 7 (when $n=10^5$):

```bash
$ cd /artifact-ccs25/rvismith/scripts/
# (around 2-3 hours using 256 cpu cores)
$ python3 Performance.py -n 100000
$ cat ./[datetime]/performance.json
```
