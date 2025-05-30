'''
given two paths of output,
return whether the output are the different
if different, return (True, line number), line number is the first different line
if the same, return (False, None)
'''
def judge(path1:str, path2:str):
    res = (False, None)
    f1 = open(path1, "r", encoding="utf-8")
    f2 = open(path2, "r", encoding="utf-8")

    lines1 = f1.readlines()
    lines2 = f2.readlines()

    if(len(lines1) != len(lines2)):
        #line number is different
        return (True, 0)
    
    size = len(lines1)
    for i in range(0, size):
        if( lines1[i] != lines2[i] ): return (True, i+1)

    f1.close()
    f2.close()
    return res

import argparse
import os
import sys

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--path1')
    parser.add_argument('--path2')
    args = parser.parse_args()
    if (not args.path1) or (os.path.exists(args.path1) == False):
        print('please specify the path to the output', file = sys.stderr)
        sys.exit(1)
    if (not args.path2) or (os.path.exists(args.path2) == False):
        print('please specify the path to the output', file = sys.stderr)
        sys.exit(1)
    different, lineNum = judge(args.path1, args.path2)
    if(different):
        # calculation error
        print(f"Fail at line {lineNum}")
    else:
        print("Pass")