# Tell cmake where to find extra Find*.cmake files (in our case the FindTCLAP.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

#Find TCLAP (a dependency of the applications only)
find_package (TCLAP REQUIRED) #via cmake/Modules/FindTCLAP.cmake
include_directories (${TCLAP_INCLUDE_DIR})

#creation of simulation library (libsimulation)
add_library(simulation Simulation.cpp Event.cpp Network.cpp Neuron.cpp UserArguments.cpp)
