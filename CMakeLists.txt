cmake_minimum_required(VERSION 4.0)
project(ProyectoFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoFinal main.cpp
        Entidad.h
        Jugador.h
        Jugador.cpp
        Habitacion.h
        Habitacion.cpp
        Direccion.h
        Entidad.cpp
        Item.h
        Item.cpp
        Enemigo.h
        Enemigo.cpp
        ServidorCorrompido.h
        ServidorCorrompido.cpp
        Parasito.h
        Parasito.cpp)
