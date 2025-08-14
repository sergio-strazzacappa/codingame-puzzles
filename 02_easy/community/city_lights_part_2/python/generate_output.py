#! /usr/bin/env python3

import sys

FILES = [
    "Point.py",
    "main.py"
]

OUTPUT_FILE = "codingame.py"

IMPORTS = [
]

try:
    output_stream = open(OUTPUT_FILE, "wt")

    for i in IMPORTS:
        output_stream.write(f"import {i}\n")

    if len(IMPORTS) > 1:
        output_stream.write("\n")

    for file in FILES:
        try:
            input_stream = open(file, "rt")
            skip_next = False
            for line in input_stream.readlines():
                if skip_next:
                    skip_next = False
                    if line == "\n":
                        continue
                if line.startswith("from") or line.startswith("import"):
                    skip_next = True
                    continue 
                output_stream.write(line)
            output_stream.write("\n")
            input_stream.close()
        except:
            print(f"Failed to open {file}", file=sys.stderr, flush=True)

    print(f"{OUTPUT_FILE} generated succesfully!")
    output_stream.close()
except:
    print(f"Failed to open {OUTPUT_FILE}", file=sys.stderr, flush=True)
