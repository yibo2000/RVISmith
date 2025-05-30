# for evaluation result
import pandas as pd
import argparse
import os
import sys

csv_path = ""
res_dict = {0:"success", 1:"all compile error", 2:"calculation error", \
            3:"emulator dumped", 4:"compiler dumped", 5:"RVISmith failed", \
            6:"partial compile error", 7:"other", 8:"timeout"}

def read_csv():
    assert(os.path.exists(csv_path))
    df = pd.read_csv(csv_path, names=["id", "seed", "data_length", "sequence_length", "root", "allin", "random", "unit", "emi"], \
                    header=None, index_col="id")
    merged = df["allin"].value_counts()
    merged = merged.add(df["random"].value_counts(), fill_value=0)
    merged = merged.add(df["unit"].value_counts(), fill_value=0)
    merged = merged.astype(int)
    #print(merged)
    total = merged.sum()
    print("sum:" , total)
    for value, count in merged.items():
        print(f"{res_dict[value]}: {count/total*100:.3f}%({count}/{total})")

    emi = df["emi"].value_counts()
    non_zero_count = df["emi"].ne(0).sum()
    print()
    print(f"emi: {non_zero_count/total*3*100:.3f}%({non_zero_count}/{int(total/3)})")
    #print(emi)
    #print(non_zero_count)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path", help="path to evaluation result (res.csv)")
    args = parser.parse_args()
    csv_path = args.path
    read_csv()