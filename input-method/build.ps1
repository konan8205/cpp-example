# LLVM for Windows and MSVC are required

$OUTPUT_DIR = "$PWD/build/windows";

if (!(Test-Path -Path $OUTPUT_DIR )) {
    New-Item -ItemType Directory -Path $OUTPUT_DIR
}

clang++ -o "$OUTPUT_DIR/im_win32.exe" -I"$PWD" im_win32.cpp -lgdi32 -luser32
