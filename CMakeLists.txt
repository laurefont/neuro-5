cmake_minimum_required (VERSION 3.1.3)
set (project_name "simulation")
project (${project_name})

# Build type : Release or Debug
set (CMAKE_BUILD_TYPE "Debug")

option (test "Build tests" ON)
option (doc "Generate Documentation" ON)
option (only-tests "Build  ONLY tests and no application" OFF)

# Use modern C++
set (CMAKE_CXX_STANDARD "14")
set (CMAKE_CXX_STANDARD_REQUIRED 1)

#Tell cmake where to find the Find*.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (CMAKE_COMPILER_IS_GNUCXX)
    # Compiler flags
    set (CMAKE_CXX_FLAGS "-Wall -pedantic")

    set (extra_warnings "-Wshadow -Wfloat-equal -Wredundant-decls -Woverloaded-virtual -Winit-self \
    -Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code -Winline -Wnon-virtual-dtor")
    set (pointer_warnings "-Wzero-as-null-pointer-constant -Wpointer-arith -Wcast-qual -Wcast-align")
    set (conversion_warnings "-Wconversion -Wdouble-promotion -Wold-style-cast")
    set (CMAKE_CXX_FLAGS_DEBUG "-g -Wextra ${extra_warnings} ${pointer_warnings} ${conversion_warnings}")
else ()
    message ("GNU Compiler Collection is not used")
endif ()

# Header files
include_directories (${PROJECT_SOURCE_DIR}/include)

#TCLAP (via cmake/Modules/FindTCLAP.cmake)
find_package (TCLAP REQUIRED)
include_directories (${TCLAP_INCLUDE_DIR})

if (NOT only-tests)
    # Create main executable
    file (GLOB_RECURSE source_files src/*.cpp)
    add_executable (${project_name} ${source_files})
endif()

# Testing with GTest
if (test)
    enable_testing ()
    find_package (GTest REQUIRED)

    # location of GTest header files
    include_directories (${GTEST_INCLUDE_DIRS})

    # Add the test/include folder to the preprocessor search path
    set (test_includes ${PROJECT_SOURCE_DIR}/test/include)
    include_directories (${test_includes})

    # Generate the list of test files
    file (GLOB_RECURSE test_files test/*.cpp)

    if (NOT only-tests)
      # remove main.cpp from the list of source files
      list (REMOVE_ITEM source_files ${PROJECT_SOURCE_DIR}/src/main.cpp)
    endif()

    # Create executable
    add_executable (${project_name}_test ${test_files} ${source_files})

    target_link_libraries (${project_name}_test ${GTEST_BOTH_LIBRARIES} pthread)
    add_test (${project_name} ${project_name}_test)
endif ()

#DOXYGEN
if (doc)
    find_package (Doxygen)
    if (DOXYGEN_FOUND)
        set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
        add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
    else()
        MESSAGE(FATAL_ERROR "Doxygen not found. Re-run cmake with -Ddoc=OFF to disable generation of documentation")
    endif()
endif()
