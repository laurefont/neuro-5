# Create main for Fixed-Step simulation with Explicit solver
file (GLOB_RECURSE source_main_fs_exp ${CMAKE_SOURCE_DIR}/apps/main_fs_exp.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable (main_fs_exp ${source_main_fs_exp})

# Create main for Fixed-Step simulation with Implicit solver
file (GLOB_RECURSE source_main_fs_imp ${CMAKE_SOURCE_DIR}/apps/main_fs_imp.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable (main_fs_imp ${source_main_fs_imp})

# Create main for simulation with Analytic Solution
file (GLOB_RECURSE source_main_as ${CMAKE_SOURCE_DIR}/apps/main_as.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable (main_as ${source_main_as})

# Add library
project(APPS)
add_library(apps main_as.cpp main_fs_exp.cpp main_fs_imp.cpp)

# Include search path
include_directories(${SRC_SOURCE_DIR})

# Specify dependency on src
target_link_libraries(apps src)
