# EXECUTABLES ####################################

add_executable (node node)
add_executable (state state)
add_executable (algorithm algorithm)

# TESTING ########################################

add_test (Node
  ${CMAKE_CURRENT_BINARY_DIR}/node)
add_test (State
  ${CMAKE_CURRENT_BINARY_DIR}/state)
add_test (Algorithm
  ${CMAKE_CURRENT_BINARY_DIR}/algorithm)

