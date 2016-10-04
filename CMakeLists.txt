cmake_minimum_required (VERSION 3.0)
project (neuro-5)

# Add the include folder to the preprocessor search path
include_directories (include)

# Generate the list of source files
file (GLOB_RECURSE source_files src/*)

# Create executable
add_executable (simulation ${source_files})

