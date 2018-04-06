# Compile full project
project(helloItk)

# Find ITK

FIND_PACKAGE(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(helloItk helloItk.cpp)

target_link_libraries(helloItk ${ITK_LIBRARIES})


