#add GoogleTest dependency
find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})

#Create executables and add tests for the three apps Neuron
#(all are linked against googletest and simulation library)

#Explicit Neuron
set (TestExecutableName ${project_name}_test_explicit)
add_executable (${TestExecutableName} ${CMAKE_CURRENT_SOURCE_DIR}/ExplicitNeuronTest.cpp)
target_link_libraries (${TestExecutableName} ${GTEST_LIBRARIES} pthread simulation)
add_test (ExplicitNeuronTests ${TestExecutableName})

#Implicit Neuron
set (TestExecutableName ${project_name}_test_implicit)
add_executable (${TestExecutableName} ${CMAKE_CURRENT_SOURCE_DIR}/ImplicitNeuronTest.cpp)
target_link_libraries (${TestExecutableName} ${GTEST_LIBRARIES} pthread simulation)
add_test (ImplicitNeuronTests ${TestExecutableName})

#Analytic Solution
set (TestExecutableName ${project_name}_test_analytic)
add_executable (${TestExecutableName} ${CMAKE_CURRENT_SOURCE_DIR}/AnalyticNeuronTest.cpp)
target_link_libraries (${TestExecutableName} ${GTEST_LIBRARIES} pthread simulation)
add_test (AnalyticNeuronTests ${TestExecutableName})

