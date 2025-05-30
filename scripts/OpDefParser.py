from typing import Dict

class OpDefInfo:
    op_type     = None
    op_id       = None
    sew         = None
    type_class  = None
    op_attr     = set()
    output_type = None
    input_num   = None
    input_types = []

    def __str__(self):
        return "CUSTOM_OP_TYPE({op_type}, {op_id}, {type_class}, {op_attr}, {output_type}, {input_num}, {input_types})".format_map(self.__dict__)
    def __eq__(self, other):
        if isinstance(other, OpDefInfo):
            return self.op_id == other.op_id and self.sew == other.sew and self.type_class == other.type_class and self.op_attr == other.op_attr and self.output_type == other.output_type and self.input_num == other.input_num and self.input_types == other.input_types
        return False

# format:
# CUSTOM_OP_TYPE(OP_TYPE, OP_ID, SEW, TYPE_CLASS, OP_ATTR, OUTPUT_TYPE,
# NUM_OF_INPUTS, INPUT_TYPE(S)...)
def parse(path):
    op_def_infos = []
    with open(path, "r") as f:
        for line in f.readlines() :
            op_def_info = parse_line(line)
            if(op_def_info == None):
                continue
            op_def_infos.append(op_def_info)
    return op_def_infos

def remove_outer_brackets(input_str: str):
    '''
    get the content in the outermost parentheses
    '''
    # Find the positions of the first '(' and the last ')'
    start = input_str.find('(') + 1
    end = input_str.rfind(')')
    
    # Extract and return the string in the middle
    return input_str[start:end].strip()

def parse_line(line: str):
    line = line.strip()
    if line.startswith("CUSTOM_OP_TYPE(") == False :
        return None
    #args = line[15:-2].split(",")
    args = remove_outer_brackets(line).split(",")
    args = list(map(lambda x: x.strip(), args))
    op_def_info = OpDefInfo()

    op_def_info.op_type = args[0]
    op_def_info.op_id = args[1]
    op_def_info.sew = args[2]
    op_def_info.type_class = args[3]
    op_def_info.op_attr = set(map(lambda x: x.strip(), args[4].split('|')))
    op_def_info.output_type = args[5]
    op_def_info.input_num = int(args[6])
    op_def_info.input_types = args[7:]
    return op_def_info