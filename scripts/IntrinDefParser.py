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

# print(parse("unsigned long __riscv_vcpop(vbool1_t vs2, size_t vl);")) # for debug