cmake_minimum_required (VERSION 3.1.3)
set (project_name "simulator")
project (${project_name})

# User options
option (test "Build test units" ON)
option (doc  "Generate Documentation" ON)

# Compilation mode (Debug or Release) and flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Force use of C++14 standard
set (CMAKE_CXX_STANDARD "14")
set (CMAKE_CXX_STANDARD_REQUIRED 1)

# Tell CMake to automatically include all files inside include folder 
include_directories (${PROJECT_SOURCE_DIR}/include)

# Tell cmake where to find extra Find*.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Simulation library (libsimulation)
add_subdirectory(src)

# Executables (linking to libsimulation)
add_subdirectory(apps)

# Optional testing with GTest (linking to libsimulation)
if (test)
    add_subdirectory(test)
else()
    MESSAGE(STATUS "Testing disabled by user (-Dtest=OFF)")
endif ()

# Option documentation generation with doxygen
if (doc)
    find_package (Doxygen)
    if (DOXYGEN_FOUND)
        set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
        add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
    else()
        MESSAGE(FATAL_ERROR "Doxygen not found. Re-run cmake with -Ddoc=OFF to disable generation of documentation.")
    endif()
endif()
