import os
import sys
import argparse

NOWPATH = os.path.dirname(os.path.abspath(__file__))
sys.path = [os.path.abspath( NOWPATH )] + sys.path
merged_txt = os.path.join(NOWPATH, '../rvv-doc/merged.txt')
if(os.path.exists( os.path.join(NOWPATH, "../rvv-doc") ) == False): os.mkdir(os.path.join(NOWPATH, "../rvv-doc"))

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
    seen = set() # remove duplicate lines
    for doc_file in doc_files:
        print(f'Read: {os.path.abspath(doc_file)}')
        with open( doc_file, 'r') as infile:
            for line in infile:
                if(line.strip().endswith(';') == True and "__riscv_" in line):
                    if line not in seen:
                        OUTFILE.write(line)
                        seen.add(line)
                else:
                    ignore.write(line)
        # OUTFILE.write('\n')
    OUTFILE.close()
    ignore.close()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('rvv_doc_path')
    args = parser.parse_args()
    if (not args.rvv_doc_path) or (os.path.exists(args.rvv_doc_path) == False):
        print('please specify the path to the list of rvv intrinsic definition', file = sys.stderr)
        sys.exit(1)

    merge2txt(args.rvv_doc_path)
    print(f'\nWrite: {os.path.abspath(merged_txt)}')
    return 0

if __name__ == "__main__":
    sys.exit(main())
