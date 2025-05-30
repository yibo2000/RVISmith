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

