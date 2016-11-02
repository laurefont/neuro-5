enable_testing ()
find_package (GTest REQUIRED)

# Generate the list of test files
file (GLOB_RECURSE test_source_files ${CMAKE_SOURCE_DIR}/src/*.cpp)

# location of GTest header files
include_directories (${GTEST_INCLUDE_DIRS})

# Add the test/include folder to the preprocessor search path
set (test_includes ${PROJECT_SOURCE_DIR}/test/include)
include_directories (${test_includes})

# Create executable
add_executable (${project_name}_test ${test_source_files})
target_link_libraries (${project_name}_test ${GTEST_BOTH_LIBRARIES} pthread)
add_test (${project_name} ${project_name}_test)

# Add library
project(TEST)
add_library(test BasicTest.cpp)

# Include search path
include_directories(${SRC_SOURCE_DIR})

# Specify dependency on src
target_link_libraries(test src)
