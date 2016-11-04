# Create main for Fixed-Step simulation with Explicit solver
file (GLOB_RECURSE source_efs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable (${project_name}_efs ${source_efs})
target_link_libraries (${project_name}_efs simulation)
