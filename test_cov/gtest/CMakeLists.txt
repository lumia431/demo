include_directories(${CMAKE_SOURCE_DIR})

add_executable(test test.cpp)

target_link_libraries(test core gtest pthread)