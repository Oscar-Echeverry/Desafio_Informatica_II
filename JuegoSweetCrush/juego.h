#ifndef JUEGO_H
#define JUEGO_H

bool detectarCombinaciones(unsigned char* tablero,
                           int filas,
                           int columnas,
                           bool* eliminados,
                           int& combinaciones);

void eliminarCombinaciones(unsigned char* tablero,
                           int filas,
                           int columnas,
                           bool* eliminados);

void aplicarGravedad(unsigned char* tablero,
                     int filas,
                     int columnas);

void generarNuevasFichas(unsigned char* tablero,
                         int filas,
                         int columnas);

int procesarCascadas(unsigned char* tablero,
                     int filas,
                     int columnas,
                     int& totalEliminados,
                     int& totalCombinaciones,
                     int& puntaje);

void llenarTableroAleatorio(unsigned char* tablero,
                            int filas,
                            int columnas);

int pedirPosicion(int filas, int columnas);

void agregarFila(unsigned char*& tablero,
                 int& filas,
                 int columnas,
                 int posicionFila,
                 int& bytesAsignados);

void eliminarFila(unsigned char*& tablero,
                  int& filas,
                  int columnas,
                  int posicionFila,
                  int& bytesAsignados);

void agregarColumna(unsigned char*& tablero,
                    int filas,
                    int& columnas,
                    int posicionColumna,
                    int& bytesAsignados);

void eliminarColumna(unsigned char*& tablero,
                     int filas,
                     int& columnas,
                     int posicionColumna,
                     int& bytesAsignados);
#endif
