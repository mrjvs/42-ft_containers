# cmake minimum version and project name
cmake_minimum_required(VERSION 3.16)
project(42-ft_containers CXX)

# set compiler flags and standard
set(CMAKE_CXX_STANDARD 98)
set(FLAGS "-O3 -Wall -Wextra -Werror -pedantic-errors")

# set cmake output directory
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

# library files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/tests/**.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/tests/**.hpp ${CMAKE_SOURCE_DIR}/src/**.hpp)

# set the include directory
include_directories(src)
include_directories(tests/_includes)

# create executable and link the library
add_executable(ft_containers_tests ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(ft_containers_tests PROPERTIES LINKER_LANGUAGE CXX)
