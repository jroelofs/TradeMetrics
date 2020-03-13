configure_file(CMakeLists.txt.in googlebench-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebench-download )
if(result)
  message(FATAL_ERROR "CMake step for googlebench failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebench-download )
if(result)
  message(FATAL_ERROR "Build step for googlebench failed: ${result}")
endif()

set(BENCHMARK_ENABLE_TESTING OFF)

# Add googlebench directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googlebench-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googlebench-build
                 EXCLUDE_FROM_ALL)

set(sources
  BenchMetrics.cpp)

add_executable(benchmarks ${sources})

target_link_libraries(benchmarks
  benchmark::benchmark
  trademetrics)