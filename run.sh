#!/bin/bash

ITERATIONS=200000
FORM="./example_forms/d_lines.json"
PARAMS="parameters.json"

# get in the root dir of the script
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit 1

# make sure the directories exist and are empty
mkdir -p ./out
mkdir -p ./plots
rm ./out/* 2>/dev/null && echo "cleaned up ./out"
rm ./plots/* 2>/dev/null && echo "cleaned up ./plots"

time ./build/main --in ./data.csv --out ./out/out.csv --iterations "$ITERATIONS" --form "$FORM" --params "$PARAMS" || exit 1

python visualize.py && echo "succesfully visualized"
python animate.py && echo "succesfully animated"
