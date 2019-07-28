#!/bin/sh

OUTPUT_DIR="$PWD/build/posix"

if [ ! -d "$OUTPUT_DIR" ]; then
	mkdir -p "$OUTPUT_DIR"
fi

g++ -o "$OUTPUT_DIR/main" -I"$PWD" main.cpp -ldl
g++ -shared -fpic -o "$OUTPUT_DIR/library.so" -I"$PWD" library.cpp
