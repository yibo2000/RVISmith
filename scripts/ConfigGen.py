# automatically evaluation config generation

compiler_flag = " -march=rv64gcv_zvfh -mabi=lp64d -Wno-psabi -static "
opts = ["-O0", "-O1", "-O2", "-O3", "-Os"]
version_llvm = ["17.0.1", "17.0.6", "18.1.0", "18.1.8", "19.1.0", "19.1.4", "20-init", "20-trunk"]
version_gcc = ["14-20240107", "14-20241116", "14.1.0", "14.2.0", "15-20240428", "15-20241117"]

def spike():
    # spike
    sim_path = "/home/emulator/riscv-isa-sim/build/spike"
    sim_flag = " --isa=rv64ima_f_d_c_v_zicsr_zifencei_zmmul_zfhmin_zve32f_zve32x_zve64d_zve64f_zve64x_zvfh_zvfhmin_zvl128b_zvl32b_zvl64b /home/riscv-files/riscv-pk/build/pk "
    for ver in version_llvm:
        ver = ver.strip()
        config_path = f"/home/configs/spike/config_llvm_{ver}.txt"
        compiler_path = f"/home/compiler/llvm/{ver}/bin/clang"
        with open(config_path, "w", encoding="utf-8") as f:
            text = f"{sim_path}\n{sim_flag}\n"
            for opt in opts:
                text += compiler_path + "\n" + compiler_flag + " " + opt + "\n"
            f.write(text)

    for ver in version_gcc:
        ver = ver.strip()
        config_path = f"/home/configs/spike/config_gcc_{ver}.txt"
        compiler_path = f"/home/compiler/gcc/{ver}/bin/gcc"
        with open(config_path, "w", encoding="utf-8") as f:
            text = f"{sim_path}\n{sim_flag}\n"
            for opt in opts:
                text += compiler_path + "\n" + compiler_flag + " " + opt + "\n"
            f.write(text)
    
def qemu():
    # qemu
    sim_path = "/home/emulator/qemu-9.1.0/build/qemu-riscv64"
    sim_flag = ""
    for ver in version_llvm:
        ver = ver.strip()
        config_path = f"/home/configs/qemu/config_llvm_{ver}.txt"
        compiler_path = f"/home/compiler/llvm/{ver}/bin/clang"
        with open(config_path, "w", encoding="utf-8") as f:
            text = f"{sim_path}\n{sim_flag}\n"
            for opt in opts:
                text += compiler_path + "\n" + compiler_flag + " " + opt + "\n"
            f.write(text)

    for ver in version_gcc:
        ver = ver.strip()
        config_path = f"/home/configs/qemu/config_gcc_{ver}.txt"
        compiler_path = f"/home/compiler/gcc/{ver}/bin/gcc"
        with open(config_path, "w", encoding="utf-8") as f:
            text = f"{sim_path}\n{sim_flag}\n"
            for opt in opts:
                text += compiler_path + "\n" + compiler_flag + " " + opt + "\n"
            f.write(text)


if __name__ == "__main__":
    spike()
    qemu()