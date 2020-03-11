set(sources
  main.cpp)

add_executable(tmctl ${sources})

target_link_libraries(tmctl trademetrics)
