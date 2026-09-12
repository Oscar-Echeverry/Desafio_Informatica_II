#ifndef TABLERO_H
#define TABLERO_H
int calcularBytes(int filas, int columnas);
unsigned char* crearTablero(int filas, int columnas);
int obtenerFicha(unsigned char* tablero, int posicion);
void ponerFicha(unsigned char* tablero, int posicion, int ficha);
void mostrarTablero(unsigned char* tablero, int filas, int columnas);
void mostrarBits(unsigned char* tablero, int filas, int columnas);
void mostrarFichasBinario(unsigned char* tablero, int filas, int columnas);
void liberarTablero(unsigned char* tablero);

#endif
