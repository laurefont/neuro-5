# Tell cmake where to find extra Find*.cmake files (in our case the FindTCLAP.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

#Find TCLAP (a dependency of the applications only)
find_package (TCLAP REQUIRED) #via cmake/Modules/FindTCLAP.cmake
include_directories (${TCLAP_INCLUDE_DIR})

#build all three applications
add_subdirectory(implicit_fixed_step)
add_subdirectory(explicit_fixed_step)
add_subdirectory(analytic_solution)
