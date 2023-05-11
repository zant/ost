# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (ost)

file(GLOB ROOT_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB ROOT_HEADER ${PROJECT_SOURCE_DIR}/src/*.h)

# The main executable
add_executable(main ${ROOT_SOURCE} ${ROOT_HEADER} ${ROOT_SOURCE_VENDOR} ${ROOT_HEADER_VENDOR})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_compile_options(main PRIVATE -Wall)
