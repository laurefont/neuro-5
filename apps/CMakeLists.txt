# Create main for Fixed-Step simulation with Explicit solver
add_executable (${project_name}_explicit main_explicit.cpp)
target_link_libraries (${project_name}_explicit simulation)

# Create main for Fixed-Step simulation with Implicit solver
add_executable (${project_name}_implicit main_implicit.cpp)
target_link_libraries (${project_name}_implicit simulation)

# Create main for Fixed-Step simulation with Analytic solver
add_executable (${project_name}_analytic_variable_step main_analytic_variable_step.cpp)
target_link_libraries (${project_name}_analytic_variable_step simulation)

# Create main for Fixed-Step simulation with User-defineable solver
add_executable (${project_name}_analytic_fixed_step main_analytic_fixed_step.cpp)
target_link_libraries (${project_name}_analytic_fixed_step simulation)


# Create main for General simulation with User-defineable solver
add_executable (${project_name} main.cpp)
target_link_libraries (${project_name} simulation)

