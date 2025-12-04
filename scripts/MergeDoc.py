import os
import sys
import argparse

NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
merged_txt = os.path.join(NOWPATH, '../rvv-doc/merged.txt')
ignored_txt = os.path.join(NOWPATH, '../rvv-doc/ignored.txt')
type_def = os.path.join(NOWPATH, '../def/Type.def')
intrinsic_def = os.path.join(NOWPATH, '../def/Intrinsic.def')

if(os.path.exists( os.path.join(NOWPATH, "../rvv-doc") ) == False): os.mkdir(os.path.join(NOWPATH, "../rvv-doc"))
if(os.path.exists( os.path.join(NOWPATH, "../def") ) == False): os.mkdir(os.path.join(NOWPATH, "../def"))

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
    ignore = open(ignored_txt, 'w', encoding='utf-8')
    for doc_file in doc_files:
        # print(f'Read: {doc_file}')
        with open( doc_file, 'r') as infile:
            for line in infile:
                if(line.strip().endswith(';') == True):
                    OUTFILE.write(line)
                else:
                    ignore.write(line)
        OUTFILE.write('\n')
    OUTFILE.close()
    ignore.close()


def gendef():
    # clear
    for defile in os.listdir( os.path.join(NOWPATH, "../def") ):
        if defile.split('.')[-1] == "def": os.remove( os.path.join(NOWPATH, "../def", defile) )
    
    # print("Parsing ...")
    type_set, defs = set(), []
    with open(merged_txt, "r", encoding="utf-8") as f_txt:
        for line in f_txt:
            if(line.strip().endswith(';') == False): continue
            parsed_dict = IntrinsicDefParser.parse(line)
            if(parsed_dict == None): continue

            # Type
            type_set.add( parsed_dict['retype'] )
            for para in parsed_dict['parameters']:
                type_set.add(para['ptype'])

            # Intrinsic
            para_list = []
            para_list.append( parsed_dict["retype"] )
            para_list.append( parsed_dict["intrinsic"] )
            para_list.append( str(parsed_dict["ratio"]))
            para_list.append( str(parsed_dict["pnum"]) )
            for para in parsed_dict["parameters"]: 
                para_list.append( f'\"{ para["ptype"] }\"' )
                para_list.append( f'\"{ para["pname"] }\"' )

            tmp = "OPDEF(" + ", ".join(para_list) + ")"
            defs.append(tmp)
    
    # generate ../def/Type.def
    print(f"Generating the Type.def file: {os.path.abspath(type_def)}")
    with open(type_def, 'w', encoding='utf-8') as f_type:
        for type_ in type_set:
            tmp = ""
            if(type_ == "void"): tmp = "BASETYPE(" + type_ + ")"
            elif(type_.startswith('v')): tmp = "VECTORTYPE(" + type_ + ")"
            else: tmp = "GENERALTYPE(" + type_ + ")"
            f_type.write(tmp+'\n')

    # generate ../def/Intrinsics.def
    print(f"Generating the Intrinsics.def file: {os.path.abspath(intrinsic_def)}")
    with open(intrinsic_def, "w", encoding="utf-8") as f_op:
        for i in range( len(defs) ):    
            f_op.write( defs[i] + '\n')

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('in_path')
    args = parser.parse_args()
    if (not args.in_path) or (os.path.exists(args.in_path) == False):
        print('please specify the path to the list of rvv intrinsic definition', file = sys.stderr)
        sys.exit(1)

    merge2txt(args.in_path)
    gendef()
    return 0

if __name__ == "__main__":
    sys.exit(main())
