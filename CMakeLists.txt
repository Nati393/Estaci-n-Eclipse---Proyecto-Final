cmake_minimum_required(VERSION 3.20)
project(ProyectoFinal)

set(CMAKE_CXX_STANDARD 20)

# Incluir todos los directorios
include_directories(${CMAKE_SOURCE_DIR})

# Encontrar todos los archivos fuente - USA MINÚSCULAS
file(GLOB_RECURSE SOURCES
        "model/*.cpp"
        "view/*.cpp"
        "controller/*.cpp"
        "main.cpp"
)

add_executable(ProyectoFinal ${SOURCES})