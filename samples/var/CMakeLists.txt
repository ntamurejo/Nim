# Compile full project
project(var)

file(GLOB ALL_FILES_CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories(${${PROJ_MAIN_NAME}_PATH}/modules/foo/include)
include_directories(${${PROJ_MAIN_NAME}_PATH}/modules/json/include)

#link_directories(${LIBRARY_OUTPUT_DIRECTORY})
add_executable(var main.cpp)

target_link_libraries(var foo json)


#install(TARGETS full DESTINATION "${CMAKE_INSTALL_PREFIX}/concept/bin")

