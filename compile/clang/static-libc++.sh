#!/bin/sh

if [ "$1" = "--help" ] || [ "$#" -eq 0 ]; then
    echo "Usage: static-libc++.sh [options] file...\n"
    echo "Note:\n\t[options]\tCommand line options are same as Clang."
    echo "\tfile...\t\tObject files should be compiled with \"-stdlib=libc++\".\n"
else
    ARCH=$(uname -m)
    LIBCPP_INCLUDE="/usr/include/c++/v1"
    LIBCPP="/usr/lib/$ARCH-linux-gnu/libc++.a"
    LIBCPPABI="/usr/lib/$ARCH-linux-gnu/libc++abi.a"

    clang++ -nostdlib++ -nostdinc++ -pthread -I$LIBCPP_INCLUDE $@ -- $LIBCPP $LIBCPPABI
fi
