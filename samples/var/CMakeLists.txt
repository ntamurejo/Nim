# Compile full project
project(var)

include_directories(${${PROJ_MAIN_NAME}_PATH}/modules/foo/include)
#link_directories(${LIBRARY_OUTPUT_DIRECTORY})
add_executable(var main.cpp)

target_link_libraries(var foo)

#install(TARGETS full DESTINATION "${CMAKE_INSTALL_PREFIX}/concept/bin")

