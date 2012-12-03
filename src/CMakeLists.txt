# CMAKE SPECIFICS ################################

cmake_minimum_required (VERSION 2.6)

# PROJECT NAME ###################################

project (matching)

# COMPILER SELECTION #############################

set (CMAKE_CXX_COMPILER "clang++")

# COMPILER OPTIONS ###############################

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")

# TESTING ########################################

enable_testing ()

# TOP LEVEL INCLUDE DIRECTORY ####################

include_directories (.)

# SUBDIRECTORIES #################################

add_subdirectory (test)

