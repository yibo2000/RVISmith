# RVISmith

RVISmith is a randomized fuzzer that generate well-defined C programs containing various RISC-V vector intrinsic (RVI) invocation sequences. It's primary purpose is to find compiler bugs related to RVV intrinsics, using differential testing as the test oracle.

## Usage

Source code of RVISmith is not public now. We provide pre-built binaries:
- `rvismith`: soft link to `rvismith-explicit`
- `rvismith-explicit`: target to explicit (non-overloaded) intrinsics, see [Appendix A](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main/auto-generated/intrinsic_funcs) in the document
- `rvismith-explicit-policy`: target to explicit (non-overloaded) intrinsics policy variants, see [Appendix B](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main/auto-generated/policy_funcs/intrinsic_funcs) in the document
- `rvismith-implicit`: target to implicit (overloaded) intrinsics, see [Appendix C](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main/auto-generated/overloaded_intrinsic_funcs) in the document
- `rvismith-implicit-policy`: target to implicit (overloaded) intrinsics policy variants, see [Appendix D](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main/auto-generated/policy_funcs/overloaded_intrinsic_funcs) in the document

```
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
After each successful execution, three C programs `allin.c`, `random.c`, and `unit.c` will be generated in the output path. RVI sequences in the three programs are deterministic and equivalent, i.e., each execution of any file is expected to print the same output.

## Artifact

For a quick start, we recommend our docker container that includes RISC-V compilers under test and other necessary environment configurations.

Available at: https://zenodo.org/records/15548270

README.md at: [README.md](https://github.com/Yibo-He/RVISmith/blob/main/artifact/README.md)

## Build from Source Code

### Prepare the list of under test rvv intrinsics

The list file should be in `txt` or `adoc` format. Each line that define a rvv intrinsic in the file should be end with **';'**, because our scripts use the ';' char to judge whether a line is a rvv intrinsic definition or irrelevant text.

We recommend to use our rvv intrinsic list files in `rvv-doc/`. We provided [RISC-V Vector Intrinsic Document](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main) in the above required format. The current implementation of RVISmith is based on this document.

### Generate the .jsonl and .def file

```
$ python3 scripts/MergeDoc.py <list_file_dir>
```

If you want to use our rvv intrinsic list files, e.g. official rvv intrinsic document v1.0-rc2:

```bash
# explicit intrinsics:
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/explicit_intrinsic_funcs
```

The script will recursively processe files in directories by `os.walk()`. The following files will be generated:

- ./def/Intrinsics_part*.def
- ./def/Types.def
- ./src/Operator_D.cpp
- ./rvv-doc/merged.txt: rvv intrinsic lines ending with ';'
- ./rvv-doc/ignored.txt: ignored lines (for debug)
- ./rvv-doc/parsed.jsonl: parsed rvv intrinsic definations in json format

To test other parts of rvv intrinsics:

```bash
# explicit intrinsics, policy variants:
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/explicit_intrinsic_funcs_policy_variants
# implicit intrinsics:
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/implicit_intrinsic_funcs
# implicit intrinsics, policy variants:
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/implicit_intrinsic_funcs_policy_variants
# all intrinsics
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/
```

### Build and use

You can compile RVISmith in two ways:

- (default and recommended) set `#define DEF_INPUT 1` in `src/Utils.hpp`: `def/*.def` is the input, compile slow, run fast. This setting is recommended when detecting bugs in compilers of a long time period.
- set `#define DEF_INPUT 0` in `src/Utils.hpp`: `.jsonl` is the input, compile fast, run slow. This setting is recommended for fast development iterations or trying RVISmith.

Compilation:

```bash
$ mkdir build && cd build
$ cmake ../
# about 5-10 minutes
$ make
```

## Useful Scripts

Several useful scripts are provided in `./scripts`.

### Requirements of the scripts
```
python >= 3.10
tqdm
numpy
json
pandas
shutil
concurrent.futures
datetime
```

### Evaluation config

Before fuzzing compilers using our scripts, an evaluation config is required. The config includes information about compiler under test, compiler flags, emulator, and emulator flags.

An example of config is shown in `scripts/config_example.txt`.
Evaluation configs are parsed by `scripts/Config.py`.

### Driver of RVISmith
The driver generates programs with **n** seeds and fuzzing with the given config in parallel. Driver code is in `scripts/RVISmithDriver.py`.

Usage:
```
python3 scripts/RVISmithDriver.py -h
usage: RVISmithDriver.py [-h] [-n NUMBER] -r RVISMITH_PATH -c CONFIG_PATH [-o OUTPUT_PATH] [--policy] [--overloaded]

options:
  -h, --help            show this help message and exit
  -n NUMBER, --number NUMBER
                        test case number
  -r RVISMITH_PATH, --rvismith_path RVISMITH_PATH
                        path to rvismith
  -c CONFIG_PATH, --config_path CONFIG_PATH
                        evaluation config path
  -o OUTPUT_PATH, --output_path OUTPUT_PATH
                        output path of test cases
  --policy              whether load-store intrinsics with policy suffixes included
  --overloaded          whether overloaded load-store intrinsics included
```

We provide a script in `scripts/Summary.py` to summarize the evaluation after using driver.

Input the `res.csv` (generated by the driver) to `Summary.py`, e.g.:
```
python3 scripts/Summary.py /home/evaluation/500000/gcc-15-20241117/20241226-125750/res.csv
sum: 1500000
success: 99.854%(1497811/1500000)
calculation error: 0.146%(2187/1500000)
emulator dumped: 0.000%(2/1500000)

emi: 0.002%(11/500000)
```

### Generate **n** programs using RVISmith (without evaluation)
Use the script `scripts/TestGen.py`
```
python3 scripts/TestGen.py -h
usage: TestGen.py [-h] -r RVISMITH_PATH -o TESTCODE_PATH [-n NUMBER] [--segment] [--policy] [--overloaded]

options:
  -h, --help            show this help message and exit
  -r RVISMITH_PATH, --rvismith_path RVISMITH_PATH
                        path to rvismith
  -o TESTCODE_PATH, --testcode_path TESTCODE_PATH
                        output path of test cases
  -n NUMBER, --number NUMBER
                        test case number
  --segment             whether segment load-store intrinsics included
  --policy              whether load-store intrinsics with policy suffixes included
  --overloaded          whether overloaded load-store intrinsics included
```


### Intrinsic coverage

#### RVISmith: `scripts/RVISmithCoverage.py`

Set appropriate `rvismith_path` and `mode` in `RVISmithCoverage.py` before use the script:

| Intrinsic                                            | RVISmith                 | Mode |
| ---------------------------------------------------- | ------------------------ | ---- |
| explicit (non-overloaded) intrinsics                 | rvismith-explicit        | 0    |
| explicit (non-overloaded) intrinsics policy variants | rvismith-explicit-policy | 1    |
| implicit (overloaded) intrinsics                     | rvismith-implicit        | 2    |
| implicit (overloaded) intrinsics policy variants     | rvismith-implicit-policy | 3    |

#### RIF: `scripts/RIFCoverage.py`

Set appropriate `rif_random_path`, `rif_fused_path`, `rif_opdef_path`, and `mode` in `RIFCoverage.py` before use the script:


### Performance of RVISmith

Set the `config`, `rvismith_path`, and `get_time()` in `scripts/Performance.py`, and then:
```
python3 scripts/Performance.py -h
usage: Performance.py [-h] [-n NUMBER]

options:
  -h, --help            show this help message and exit
  -n NUMBER, --number NUMBER
                        number of test cases
```

## Reported Bugs

| ID   | Compiler | Type                | Status    | Report                                                       | Description                                                  |
| ---- | -------- | ------------------- | --------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1    | GCC      | Crash               | Fixed     | [117286](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=117286) | ICE during `vlmul_ext` and `vlmul_trunc` pass                |
| 2    | GCC      | Crash               | Confirmed | [117877](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=117877) | ICE during printing error message                            |
| 3    | GCC      | Error results       | Confirmed | [117947](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=117947) | `vlenb` after an inappropriate `vsetvli`                     |
| 4    | GCC      | Error results       | Confirmed | [117953](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=117953) | Missing `csrwi` to modify `vxrm`                             |
| 5    | GCC      | Illegal instruction | Confirmed | [117955](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=117955) | Illegal riscv instruction `vsetvli zero,zero,e64,mf4,ta,ma`  |
| 6    | GCC      | Segment Fault       | Confirmed | [118100](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=118100) | Segment Fault by rvv intrinsic compilation at `-O2` and `-O3` |
| 7    | GCC      | Error results       | Confirmed | [118103](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=118103) | Missing the `fsrm` instruction to the recover status of the `frm` CSR |
| 8    | LLVM     | Illegal instruction | Fixed     | [117909](https://github.com/llvm/llvm-project/issues/117909) | Illegal instruction by Clang for FP rounding mode intrinsics |
| 9    | XuanTie  | Crash               | Fixed     | *                                                            | ICE during `vlmul_ext` and `vlmul_trunc` pass                |
| 10   | XuanTie  | Error results       | Confirmed | *                                                            | `vlenb` after an inappropriate `vsetvli`                     |
| 11   | XuanTie  | Segment Fault       | Confirmed | *                                                            | Segment Fault by rvv intrinsic compilation at `-O2` and `-O3` |
| 12   | XuanTie  | Illegal instruction | Confirmed | *                                                            | Illegal instruction by masked widening integer operations    |
| 13   | XuanTie  | Error results       | Confirmed | *                                                            | Missing the `fsrm` instruction to recover the status of frm CSR |


## Acknowledgement

- [RISC-V Vector Intrinsic Document](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main)
- [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
- [RVV Intrinsic Fuzzing (RIF)](https://github.com/sifive/riscv-vector-intrinsic-fuzzing)
- [GCC, the GNU Compiler Collection](https://gcc.gnu.org)
- [The **LLVM** Compiler Infrastructure](https://llvm.org)
- [XuanTie](https://www.xrvm.com)
