#!/bin/bash

mkdir ../bin

filenames=$(find ./src/modules/ -type f -name "*.c")

echo "Files: " $filenames

compiler_flags="-g -shared -fdeclspec -fPIC"
include_directories="-Isrc"
linker_flags="-lvulkan -lwayland-client"
defines="-DCOMPILE_DEBUG -DWF_EXPORT"

echo "Building Engine..."
clang $filenames $compiler_flags -o ../bin/libwaterfall.so $defines $include_directories $linker_flags
echo "Done."
