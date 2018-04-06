# Compile full project
project(helloVtk)

# Find ITK

FIND_PACKAGE(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(helloVtk helloVtk.cpp)

target_link_libraries(helloVtk ${VTK_LIBRARIES})


