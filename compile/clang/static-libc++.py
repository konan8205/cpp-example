#!/usr/bin/python3

import os
import sys
import subprocess

help_usage = """Usage:    static-libc++.py [version] [options]
Note:
    [version]:  LLVM version
    [options]:  Clang options
"""

if len(sys.argv) < 3:
    print(help_usage)
    sys.exit(1)

llvm_version = sys.argv[1]
libcpp_include = "/usr/lib/llvm-" + llvm_version + "/include/c++/v1"
libcpp_lib = "/usr/lib/llvm-" + llvm_version + "/lib/libc++.a"
libcppabi_lib = "/usr/lib/llvm-" + llvm_version + "/lib/libc++abi.a"

clang_argv = ['clang++-' + llvm_version]
for idx in range(2, len(sys.argv)):
    print(sys.argv[idx])
    clang_argv.append(sys.argv[idx])

proc = subprocess.Popen(clang_argv)
proc.wait()
