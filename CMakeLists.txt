# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (ost)

add_subdirectory(test)

file(GLOB ROOT_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cc)

# Create a library from your source files
add_library(ost ${ROOT_SOURCE})

target_include_directories(ost PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_property(TARGET ost PROPERTY CXX_STANDARD 20)
target_compile_options(ost PRIVATE -Wall -Werror -Wextra -Wpedantic -Wvla -Wextra-semi -Wnull-dereference -Wswitch-enum)

add_subdirectory(lib/fmt EXCLUDE_FROM_ALL)
target_link_libraries(ost fmt::fmt)

add_subdirectory(lib/magic_enum EXCLUDE_FROM_ALL)
target_link_libraries(ost magic_enum)

# The main executable
# add_executable(main ${PROJECT_SOURCE_DIR}/src/Main.cpp)
# set_property(TARGET main PROPERTY CXX_STANDARD 20)
# target_compile_options(main PRIVATE -Wall)
# target_link_libraries(main PRIVATE ost)

# Test
