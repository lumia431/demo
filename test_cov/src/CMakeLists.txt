include_directories(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp)

target_link_libraries(main core gtest)


