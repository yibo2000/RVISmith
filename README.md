# Building RVISmith
Source code of RVISmith.
RVISmith is a random generator of C programs that contain various risc-v vector intrinsic (RVI) sequences. It's primary purpose is to find compiler bugs related to compiler support for RVI, using differential testing as the test oracle.

## Requirements
```
cmake >= 3.0
python3
```

### Build and use

Compilation:
```bash
$ mkdir build && cd build
$ cmake ../
$ make
```

The executable file of RVISmith will be generated in `build/RVISmith`:
```bash
$ ./RVISmith -h
One line description of RVISmith
Usage:
  RVISmith [OPTION...]

  -s, --seed arg             Seed (default: 0xdeadbeef)
  -l, --data_length arg      Data length (default: 10)
  -n, --sequence_length arg  Sequence length (default: 10)
  -o, --output arg           Output path (default: ./)
      --log-coverage         Save the coverage information to 
                             'coverage.bin' (default: false)
      --cov-guidance         Enable coverage guidance and save the coverage 
                             information to 'coverage.bin' (default: false)
      --cov-clean            Clean the coverage data in 'coverage.bin' 
                             (default: false)
      --print-cov            Print the coverage information in 
                             'coverage.bin' (default: false)
  -h, --help                 Print usage
```