# Compile full project
project(sample-lines)

file(GLOB ALL_FILES_CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories(${${PROJ_MAIN_NAME}_PATH}/modules/lines/include)

#link_directories(${LIBRARY_OUTPUT_DIRECTORY})
add_executable(sample-lines main.cpp)

target_link_libraries(sample-lines lines ${ITK_LIBRARIES})


#install(TARGETS full DESTINATION "${CMAKE_INSTALL_PREFIX}/concept/bin")

