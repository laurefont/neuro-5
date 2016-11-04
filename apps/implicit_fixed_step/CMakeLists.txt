# Create main for Fixed-Step simulation with Implicit solver
file (GLOB_RECURSE source_ifs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable (${project_name}_ifs ${source_ifs})
target_link_libraries (${project_name}_ifs simulation)
