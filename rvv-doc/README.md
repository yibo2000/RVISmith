### The list of under test rvv intrinsics
We provide a script in `scripts/PreprocessDoc.py` to pre-process rvv definition files in `txt` or `adoc` format. Each line that define a rvv intrinsic in the file should be end with **';'**, because our scripts use the ';' char to judge whether a line is a rvv intrinsic definition or irrelevant text. 

We provided [RISC-V Vector Intrinsic Document](https://github.com/riscv-non-isa/rvv-intrinsic-doc/tree/main) in the above required format located in `rvv-doc/rvv-intrinsic-doc-1.0-rc2`. The current implementation of RVISmith is based on this document.

```
$ cd rvismith-repo
$ python3 scripts/MergeDoc.py ./rvv-doc/rvv-intrinsic-doc-1.0-rc2/explicit_intrinsic_funcs
```

The script will recursively processe files in directories by `os.walk()`. The following files will be generated:
- ./rvv-doc/merged.txt: rvv intrinsic lines ending with ';'
- ./rvv-doc/ignored.txt: ignored lines in the document (for debug)

You can also use our pre-processed files in `rvv-doc/rvv-intrinsic-list`. These files are typically used when generating rvv **intrinsic coverage**.