# Create main for simulation with Analytic Solution
file (GLOB_RECURSE source_as ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable (${project_name}_as ${source_as})
target_link_libraries (${project_name}_as simulation)

