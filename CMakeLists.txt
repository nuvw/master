# CMAKE SPECIFICS ################################

cmake_minimum_required (VERSION 2.6)

# PROJECT NAME ###################################

project (GGC)

# COMPILER OPTIONS ###############################

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG "-g")

# TESTING ########################################

enable_testing ()

# INCLUDE DIRECTORIES ############################

include_directories (include)
include_directories (header)
include_directories (src)

# SUBDIRECTORIES #################################

add_subdirectory (experiments)
add_subdirectory (test)

