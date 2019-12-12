# LLVM for Windows and MSVC are required

$OUTPUT_DIR = "$PWD/build/windows";

if (!(Test-Path -Path $OUTPUT_DIR )) {
    New-Item -ItemType Directory -Path $OUTPUT_DIR
}

clang++ -o "$OUTPUT_DIR/sl_main.exe" -I"$PWD" sl_main.cpp
clang++ -shared -o "$OUTPUT_DIR/sl_lib.dll" -I"$PWD" sl_lib.cpp
