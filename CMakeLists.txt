cmake_minimum_required(VERSION 3.26)
project(proyecto_SDL_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proyecto_SDL_final
        x64/Debug/main.cpp
        animaciones.h
        avion.h
        bala.h
        balaTipo1.h
        enemigo.h
        enemigo1.h
        enemigo2.h
        general.h
        imagen.h
        main.cpp
        misil.h
        musica.h
        proyectil.h)
