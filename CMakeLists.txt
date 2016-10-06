cmake_minimum_required (VERSION 3.1.3)
project (neuro-5)

# Build type : None or Debug
set (CMAKE_BUILD_TYPE "Debug")

# Use modern C++
set (CMAKE_CXX_STANDARD "14")
set (CMAKE_CXX_STANDARD_REQUIRED 1)

# Compiler flags
set (CMAKE_CXX_FLAGS "-Wall -pedantic")

set (extra_warnings "-Wshadow -Wfloat-equal -Wredundant-decls -Woverloaded-virtual -Winit-self \
-Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code -Winline -Wnon-virtual-dtor")
set (pointer_warnings "-Wzero-as-null-pointer-constant -Wpointer-arith -Wcast-qual -Wcast-align")
set (conversion_warnings "-Wconversion -Wdouble-promotion -Wold-style-cast")
set (CMAKE_CXX_FLAGS_DEBUG "-g -Wextra ${extra_warnings} ${pointer_warnings} ${conversion_warnings}")

# Add the include folder to the preprocessor search path
include_directories (include)

# Generate the list of source files
file (GLOB_RECURSE source_files src/*)

# Create executable
add_executable (simulation ${source_files})

