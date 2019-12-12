#!/bin/sh

OUTPUT_DIR="$PWD/build/posix"

if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

g++ -o "$OUTPUT_DIR/sl_main" -I"$PWD" sl_main.cpp -ldl && \
g++ -shared -fpic -o "$OUTPUT_DIR/sl_lib.so" -I"$PWD" sl_lib.cpp
