# CMAKE SPECIFICS ################################

cmake_minimum_required (VERSION 2.6)

# PROJECT NAME ###################################

project (PerfectMatchingsCounter)

# COMPILER OPTIONS ###############################

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")

# TESTING ########################################

enable_testing ()

# INCLUDE DIRECTORIES ############################

include_directories (include)
include_directories (src)

# SUBDIRECTORIES #################################

add_subdirectory (test)
add_subdirectory (profiler)

