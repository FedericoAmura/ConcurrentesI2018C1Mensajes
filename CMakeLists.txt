cmake_minimum_required(VERSION 3.10)
project(mensajes)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/Cliente")
add_subdirectory("${PROJECT_SOURCE_DIR}/Cola")
add_subdirectory("${PROJECT_SOURCE_DIR}/Servidor")
add_subdirectory("${PROJECT_SOURCE_DIR}/Util")


add_executable(mensajes ${SOURCE} ${HEADERS})
