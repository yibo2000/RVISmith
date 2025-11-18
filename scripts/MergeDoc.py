import os
import sys
import argparse
import json

NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
merged_txt = os.path.join(NOWPATH, '../rvv-doc/merged.txt')
parsed_json = os.path.join(NOWPATH, '../rvv-doc/parsed.jsonl')
type_def = os.path.join(NOWPATH, '../def/Types.def')
cpp_path = os.path.join(NOWPATH, '../src/Operator_D.cpp')

part_size = 1000 # number of intrinsics in per part
total_size = 0
index_list = []

if(os.path.exists( os.path.join(NOWPATH, "../rvv-doc") ) == False): os.mkdir(os.path.join(NOWPATH, "../rvv-doc"))
if(os.path.exists( os.path.join(NOWPATH, "../def") ) == False): os.mkdir(os.path.join(NOWPATH, "../def"))

type_set = set()

import IntrinsicDefParser

def merge2txt(directory):
    # Input
    doc_files = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if(file.endswith('.txt') or file.endswith('.adoc')):
                doc_files.append(os.path.join(root,file))
    doc_files.sort()

    # Output
    OUTFILE = open(merged_txt, 'w', encoding='utf-8')
    ignore = open(os.path.join(NOWPATH, '../rvv-doc/ignored.txt'), 'w', encoding='utf-8')
    for doc_file in doc_files:
        print(f'Read: {doc_file}')
        with open( doc_file, 'r') as infile:
            for line in infile:
                if(line.strip().endswith(';') == True):
                    OUTFILE.write(line)
                else:
                    ignore.write(line)
        OUTFILE.write('\n')
    OUTFILE.close()
    ignore.close()

def merge2json():
    print(f"Generating the jsonl file: {os.path.abspath(parsed_json)}")
    with open(parsed_json, "w", encoding="utf-8") as f_json:
        with open(merged_txt, "r", encoding="utf-8") as f_txt:
            for line in f_txt:
                if(line.strip().endswith(';') == False): continue
                parsed_dict = IntrinsicDefParser.parse(line)
                if(parsed_dict == None): continue

                type_set.add( parsed_dict['retype'] )
                for para in parsed_dict['parameters']:
                    type_set.add(para['ptype'])

                f_json.write(json.dumps(parsed_dict)+'\n')

def gendef():
    global total_size, index_list 
    # clear
    for defile in os.listdir( os.path.join(NOWPATH, "../def") ):
        if defile.split('.')[-1] == "def": os.remove( os.path.join(NOWPATH, "../def", defile) )
    # generate ../def/Types.def
    print(f"Generating the Types.def file: {os.path.abspath(type_def)}")
    with open(type_def, 'w', encoding='utf-8') as f_type:
        for type_ in type_set:
            tmp = ""
            if(type_ == "void"): tmp = "BASETYPE(" + type_ + ")"
            elif(type_.startswith('v')): tmp = "VECTORTYPE(" + type_ + ")"
            else: tmp = "GENERALTYPE(" + type_ + ")"
            f_type.write(tmp+'\n')

    # generate ../def/Intrinsics.def
    print(f"Generating the Intrinsics.def file ... ")
    defs = []
    with open(parsed_json, "r", encoding="utf-8") as f_json:
        for line in f_json:
            json_obj = json.loads(line)
            para_list = []
            para_list.append( json_obj["retype"] )
            para_list.append( json_obj["intrinsic"] )
            para_list.append( str(json_obj["pnum"]) )
            for para in json_obj["parameters"]: 
                para_list.append( f'\"{ para["ptype"] }\"' )
                para_list.append( f'\"{ para["pname"] }\"' )

            tmp = "OPDEF(" + ", ".join(para_list) + ")"
            defs.append(tmp)

    total_size, f_op = len(defs), None
    for i in range( len(defs) ):
        if (i % part_size == 0):
            if(f_op != None): f_op.close()
            op_def = os.path.join(NOWPATH, f'../def/Intrinsics_part{int(i / part_size)}.def')
            f_op = open(op_def, 'w', encoding='utf-8')
            index_list.append( int(i / part_size) )
        f_op.write( defs[i] + '\n' )
    f_op.close()


head = '''/*
Compile slow, run fast (read from .def).
DEF_INPUT is defined in Utils.hpp
set (JSON_INPUT = 0 and DEF_INPUT = 1) will run this file
*/

#include "Operator.hpp"

#if DEF_INPUT
'''

end = '''
#endif // DEF_INPUT
'''

def get_part_code(i):
    part_template = f'''
std::vector<BaseOperator* > getOpDefinitions{i}(){{
    std::vector<BaseOperator* > res;

#define OPDEF(RETYPE, NAME, PNUM, ...) {{ BaseOperator *ptr = new BaseOperator( std::string(#RETYPE), std::string(#NAME), PNUM, {{__VA_ARGS__}} ); res.push_back( ptr ); }}

#include "Intrinsics_part{i}.def"
#undef OPDEF

    return res;
}}
'''
    return part_template

def gen_sum_code():
    ll = []
    for index in index_list:
        ll.append( f"\tthis->extend( getOpDefinitions{index}() );" )
    ll_str = '\n'.join(ll)
    sum_template = f'''
void OpDEFS::initializeOpDefinitions(){{
{ ll_str }
}}
'''
    return sum_template

def gen_Operator_D_cpp():
    print(f"Generating the Operator_D.cpp file: {os.path.abspath(cpp_path)}")
    f_cpp = open(cpp_path, "w", encoding="utf-8")
    f_cpp.write(head)
    for index in index_list:
        f_cpp.write(get_part_code(index))
    f_cpp.write( gen_sum_code() )
    f_cpp.write(end)
    f_cpp.close()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('in_path')
    args = parser.parse_args()
    if (not args.in_path) or (os.path.exists(args.in_path) == False):
        print('please specify the path to the list of rvv intrinsic definition', file = sys.stderr)
        sys.exit(1)

    merge2txt(args.in_path)
    merge2json()
    gendef()
    gen_Operator_D_cpp()
    return 0

if __name__ == "__main__":
    sys.exit(main())
