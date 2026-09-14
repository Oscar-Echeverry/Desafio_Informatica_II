cmake_minimum_required(VERSION 3.16)

project(JuegoSweetCrush LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(JuegoSweetCrush main.cpp
    tablero.h
    juego.h
    juego.cpp)

include(GNUInstallDirs)
install(TARGETS JuegoSweetCrush
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
