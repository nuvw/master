# EXECUTABLES ####################################

add_executable (node_test
  node_test)
add_executable (state_test
  state_test)
add_executable (algorithm_test
  algorithm_test)

# TESTING ########################################

add_test (Node
  ${CMAKE_CURRENT_BINARY_DIR}/node_test)
add_test (State
  ${CMAKE_CURRENT_BINARY_DIR}/state_test)
add_test (Algorithm
  ${CMAKE_CURRENT_BINARY_DIR}/algorithm_test)

