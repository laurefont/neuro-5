find_package (GTest REQUIRED)

# Generate the list of test files
file (GLOB_RECURSE test_source_files ${CMAKE_SOURCE_DIR}/test/*.cpp)

# location of GTest header files
include_directories (${GTEST_INCLUDE_DIRS})

#Create executable linked against googletest library
set (TestExecutableName ${project_name}_test)
add_executable (${TestExecutableName} ${test_source_files})
target_link_libraries (${TestExecutableName} ${GTEST_LIBRARIES} pthread simulation)

#Add tests
add_test (AllSimulationTests ${TestExecutableName})
add_custom_target(check
                  COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS ${TestExecutableName})

