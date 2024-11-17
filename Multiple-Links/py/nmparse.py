#! /usr/bin/env python3

import os
import re
import sys
import struct

if __name__ == "__main__":

    nm_file = sys.argv[1]
    nm_data = {}

    print("#include <symbol.h>")
    if not os.path.exists(nm_file):
        print("struct symbol_table symbol_tabel[] = {};")
        print("unsigned long symbol_num = 0;")
        exit(0)

    with open(nm_file) as f:
        nm_output = f.read()
        for line in nm_output.splitlines():
            unit = line.strip().split(" ")
            nm_data[unit[-1].replace(" ", "")] = {
                "addr": unit[0] if len(unit[0]) > 1 else "00",
                "size": unit[-3] if unit[-2] == 'b' else 0x0,
                "mask": unit[-2],
            }

    print("struct symbol_table symbol_tabel[] = {")
    for sym in nm_data.keys():

        desc = nm_data[sym]
        print(f"\"{sym}\"", end=", ")

        addr = desc["addr"]
        print(f"0x{addr}",end = ", ")

        size = desc["size"]
        mask = desc["mask"]
        print(f"0x{size}, \'{mask}\'", end=",\n")

    print("};")
    print(f"unsigned long symbol_num = {len(nm_data.keys())};")
