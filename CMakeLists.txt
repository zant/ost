# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (ost)

add_subdirectory(test)

file(GLOB ROOT_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB ROOT_HEADER ${PROJECT_SOURCE_DIR}/src/*.h)

# Create a library from your source files
add_library(ost ${ROOT_SOURCE} ${ROOT_HEADER})

set_property(TARGET ost PROPERTY CXX_STANDARD 20)
target_compile_options(ost PRIVATE -Wall)

add_subdirectory(include/fmt EXCLUDE_FROM_ALL)
target_link_libraries(ost fmt::fmt)

add_subdirectory(include/magic_enum EXCLUDE_FROM_ALL)
target_link_libraries(ost magic_enum)

# The main executable
# add_executable(main ${PROJECT_SOURCE_DIR}/src/Main.cpp)
# set_property(TARGET main PROPERTY CXX_STANDARD 20)
# target_compile_options(main PRIVATE -Wall)
# target_link_libraries(main PRIVATE ost)

# Test
