#TCLAP is a dependency of the applications only
find_package (TCLAP REQUIRED) #via cmake/Modules/FindTCLAP.cmake
include_directories (${TCLAP_INCLUDE_DIR})

# Create main for Fixed-Step simulation with Explicit solver
file (GLOB_RECURSE source_fs_exp ${CMAKE_SOURCE_DIR}/apps/main_fs_exp.cpp)
add_executable (${project_name}_fs_exp ${source_fs_exp})
target_link_libraries (${project_name}_fs_exp simulation)

# Create main for Fixed-Step simulation with Implicit solver
file (GLOB_RECURSE source_fs_imp ${CMAKE_SOURCE_DIR}/apps/main_fs_imp.cpp)
add_executable (${project_name}_fs_imp ${source_fs_imp})
target_link_libraries (${project_name}_fs_imp simulation)

# Create main for simulation with Analytic Solution
file (GLOB_RECURSE source_as ${CMAKE_SOURCE_DIR}/apps/main_as.cpp)
add_executable (${project_name}_as ${source_as})
target_link_libraries (${project_name}_as simulation)

