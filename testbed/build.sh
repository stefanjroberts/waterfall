#!/bin/bash

mkdir ../bin

compiler_flags="-g -fdeclspec -fPIC"
include_directories="-Isrc -I../engine/src/"
linker_flags="-L../bin/ -lwaterfall -Wl,-rpath,. "
defines="-DCOMPILE_DEBUG -DWF_IMPORT"

echo "Building Testbed..."
clang main.c $compiler_flags -o ../bin/testbed $defines $include_directories $linker_flags
echo "Done."
