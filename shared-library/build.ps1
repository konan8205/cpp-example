# LLVM for Windows and MSVC are required

$OUTPUT_DIR = "$PWD/build/windows";

if (!(Test-Path -Path $OUTPUT_DIR )) {
    New-Item -ItemType Directory -Path $OUTPUT_DIR
}

clang++ -o "$OUTPUT_DIR/main.exe" -I"$PWD" main.cpp
clang++ -shared -o "$OUTPUT_DIR/library.dll" -I"$PWD" library.cpp
