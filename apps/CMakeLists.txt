#TCLAP is a dependency of the applications only
find_package (TCLAP REQUIRED) #via cmake/Modules/FindTCLAP.cmake
include_directories (${TCLAP_INCLUDE_DIR})

#build all three applications
add_subdirectory(implicit_fixed_step)
add_subdirectory(explicit_fixed_step)
add_subdirectory(analytic_solution)
