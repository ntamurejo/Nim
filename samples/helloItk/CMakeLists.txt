# Compile full project
project(helloItk)

add_executable(helloItk helloItk.cpp)

target_link_libraries(helloItk ${ITK_LIBRARIES})


