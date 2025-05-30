import os

class Config:
    config_path = ""
    # path to compiler under test and emulator
    sim_path = ""
    sim_flag = ""
    compiler_paths = []
    compiler_flags = []

    def __init__(self, config_path):
        self.config_path = config_path
        self.loadConfig()
    
    def loadConfig(self):
        assert ( os.path.exists(self.config_path) )
        with open(self.config_path, "r", encoding="utf-8") as config:
            lines = config.readlines()
            assert( len(lines) >= 4 )
            self.sim_path = lines[0].strip()
            self.sim_flag = lines[1].strip()
            i = 2
            while(i<len(lines)):
                self.compiler_paths.append(lines[i].strip())
                self.compiler_flags.append(lines[i+1].strip())
                i += 2
        assert(self.sim_path != "")
        assert(self.compiler_paths != [])
        assert(self.compiler_flags != [])
        assert( len(self.compiler_paths) == len(self.compiler_flags) )
        assert ( os.path.exists(self.sim_path) )
        for path in self.compiler_paths:
            assert ( os.path.exists(path) )

    def printConfig(self):
        # for debug
        print(f"sim_path = {self.sim_path}")
        print(f"sim_flag = {self.sim_flag}")
        print(f"compiler_paths = {self.compiler_paths}")
        print(f"compiler_flags = {self.compiler_flags}")