# Create main for Fixed-Step simulation with Explicit solver
add_executable (${project_name}_explicit main_explicit.cpp)
target_link_libraries (${project_name}_explicit simulation)

# Create main for Fixed-Step simulation with Implicit solver
add_executable (${project_name}_implicit main_implicit.cpp)
target_link_libraries (${project_name}_implicit simulation)

# Create main for Fixed-Step simulation with Analytic solver
add_executable (${project_name}_analytic main_analytic.cpp)
target_link_libraries (${project_name}_analytic simulation)

# Create main for Fixed-Step simulation with User-defineable solver
add_executable (${project_name} main.cpp)
target_link_libraries (${project_name} simulation)
