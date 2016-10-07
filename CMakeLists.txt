cmake_minimum_required (VERSION 3.1.3)
set (project_name "simulation")
project (${project_name})

# Build type : None or Debug
set (CMAKE_BUILD_TYPE "Debug")

# Use modern C++
set (CMAKE_CXX_STANDARD "14")
set (CMAKE_CXX_STANDARD_REQUIRED 1)

if (CMAKE_COMPILER_IS_GNUCXX)
    # Compiler flags
    set (CMAKE_CXX_FLAGS "-Wall -pedantic")

    set (extra_warnings "-Wshadow -Wfloat-equal -Wredundant-decls -Woverloaded-virtual -Winit-self \
    -Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code -Winline -Wnon-virtual-dtor")
    set (pointer_warnings "-Wzero-as-null-pointer-constant -Wpointer-arith -Wcast-qual -Wcast-align")
    set (conversion_warnings "-Wconversion -Wdouble-promotion -Wold-style-cast")
    set (CMAKE_CXX_FLAGS_DEBUG "-g -Wextra ${extra_warnings} ${pointer_warnings} ${conversion_warnings}")
else ()
    message ("GNU Compiler Collection is not used")
endif ()

# Add the include folder to the preprocessor search path
set (common_includes ${PROJECT_SOURCE_DIR}/include)
include_directories (${common_include})

# Generate the list of source files
file (GLOB_RECURSE source_files src/*.cpp)

# Create executable
add_executable (${project_name} ${source_files})

