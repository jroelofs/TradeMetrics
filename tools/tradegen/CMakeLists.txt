set(sources
  main.cpp)

add_executable(tradegen ${sources})

target_link_libraries(tradegen trademetrics)
