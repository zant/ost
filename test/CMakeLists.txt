cmake_minimum_required (VERSION 3.1)

option(BUILD_TESTS "Build the tests" OFF)

file(GLOB ROOT_SOURCE ${PROJECT_SOURCE_DIR}/test/*.cc)

if (BUILD_TESTS)
  add_subdirectory(include/Catch2)
  add_executable(tests ${ROOT_SOURCE})

  set_property(TARGET tests PROPERTY CXX_STANDARD 20)
  target_compile_options(tests PRIVATE -Wall)

  target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  target_link_libraries(tests PRIVATE ost)
endif()