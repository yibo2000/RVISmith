import re

def parse(api_str: str):
    '''
    input the definition of rvv c intrinsic api, out the parsed dictionary of the intrinsic.
    example input: 'vint16m1_t vle16_v_int16m1_tamu (vbool16_t mask, vint16m1_t merge, const int16_t *base, size_t vl);'
    example output: 
    { 'retype': 'vint16m1_t',
    'intrinsic': 'vle16_v_int16m1_tamu',
    'pnum': 4,
    'parameters': [{'ptype':'vbool16_t', 'pname': 'mask'}, {'ptype':'vint16m1_t', 'pname': 'merge'}, 
    {'ptype':'const int16_t *', 'pname': 'base'}, {'ptype':'size_t', 'pname': 'vl'}]
    }
    '''
    res = {}
    api_str = clean_str(api_str)
    if(api_str == ''): return None
    
    # Step 1: Split the string to extract the return type and the rest
    parts = clean_str(api_str[0: api_str.find('(')]).split(' ')
    res['retype'] =  clean_str(' '.join(parts[0:-1]))
    res['intrinsic'] = clean_str(parts[-1])
    
    # Step 2: Extract function name and parameters
    params = remove_outer_brackets(api_str)
    
    # Step 3: Remove the closing parenthesis and split the parameters
    if(params!=''): params = params.split(',')
    else: params = []
    res['pnum'] = len(params)
    
    # Step 4: Extract parameter type and name
    para_list = []
    for param in params:
        param_parts = param.rsplit(' ', 1)
        if(param_parts[1].strip()[0] == '*'):
            param_parts[0] = param_parts[0].strip() + ' *'
            param_parts[1] = param_parts[1].strip()[1:]
        else:
            param_parts[0] = param_parts[0].strip()
            param_parts[1] = param_parts[1].strip()
        para_list.append({
            'ptype': clean_str(param_parts[0]),
            'pname': clean_str(param_parts[1])
        })
    res['parameters'] = para_list

    # Step 5: Determine the common ratio
    ratios = set()
    ratio = vtype_ratio(res['retype'])
    if ratio is not None: ratios.add(ratio)
    
    vector_patten = re.compile(r"v.+_t")
    for para in para_list:
        ptype = para['ptype']
        if vector_patten.match(ptype):
            ratio = vtype_ratio(ptype)
            if ratio is not None: ratios.add(ratio)
    
    if len(ratios) == 1: res['ratio'] = ratios.pop()
    else: res['ratio'] = 0
    return res


def remove_outer_brackets(input_str: str):
    '''
    get the content in the outermost parentheses
    '''
    # Find the positions of the first '(' and the last ')'
    start = input_str.find('(') + 1
    end = input_str.rfind(')')
    
    # Extract and return the string in the middle
    return input_str[start:end].strip()


def clean_str(input_str: str):
    '''
    remove the space outside, merge adjacent spaces
    '''
    return re.sub(r'\s+', ' ', input_str).strip()


def vtype_ratio(vector_type: str) -> int:
    '''
    return the ratio of vector type.
    e.g., input "vuint8m2_t", output 4
    '''
    # Group 1: type (e.g., uint, float)
    # Group 2: width (e.g., 8, 32) -> ewidth
    # Group 3: mul (e.g., m1, mf2, m8) -> emul
    # Group 4: nfield (e.g., x2)
    vnum_pattern = re.compile(r"v([a-z]+)([0-9]+)(m[f0-9]+)([x1-8]*)_t")
    vbool_pattern = re.compile(r"vbool([0-9]+)_t")

    match_num = vnum_pattern.search(vector_type)
    if match_num:
        ewidth = int(match_num.group(2))
        emul = match_num.group(3)

        if emul == "mf8": return ewidth * 8
        elif emul == "mf4": return ewidth * 4
        elif emul == "mf2": return ewidth * 2
        elif emul == "m1": return ewidth
        elif emul == "m2": return ewidth // 2 
        elif emul == "m4": return ewidth // 4
        elif emul == "m8": return ewidth // 8
            
    # bool types
    match_bool = vbool_pattern.search(vector_type)
    if match_bool:
        ewidth = int(match_bool.group(1))
        return ewidth
    
    return None

# print(parse("vfloat32m1_t __riscv_vfwredusum_vs_f16m8_f32m1_m(vbool2_t vm, vfloat16m8_t vs2, vfloat32m1_t vs1, size_t vl);")) # for debug