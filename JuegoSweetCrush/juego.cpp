#include <iostream>
#include <cstdlib>

#include "juego.h"
#include "tablero.h"

using namespace std;

bool detectarCombinaciones(unsigned char* tablero,
                           int filas,
                           int columnas,
                           bool* eliminados,
                           int& combinaciones)
{
    bool encontro = false;
    combinaciones = 0;

    for (int fila = 0; fila < filas; fila++)
    {
        int columna = 0;

        while (columna < columnas)
        {
            int posicion = fila * columnas + columna;
            int ficha = obtenerFicha(tablero, posicion);

            if (ficha == 0)
            {
                columna++;
                continue;
            }

            int inicio = columna;
            int contador = 1;

            while (columna + contador < columnas)
            {
                int siguiente = fila * columnas
                                + columna + contador;

                int siguienteFicha =
                    obtenerFicha(tablero, siguiente);

                if (siguienteFicha == ficha)
                    contador++;
                else
                    break;
            }

            if (contador >= 3)
            {
                combinaciones++;
                encontro = true;

                for (int i = 0; i < contador; i++)
                {
                    int posicionEliminar =
                        fila * columnas + inicio + i;

                    eliminados[posicionEliminar] = true;
                }
            }

            columna = inicio + contador;
        }
    }

    for (int columna = 0; columna < columnas; columna++)
    {
        int fila = 0;

        while (fila < filas)
        {
            int posicion = fila * columnas + columna;
            int ficha = obtenerFicha(tablero, posicion);

            if (ficha == 0)
            {
                fila++;
                continue;
            }

            int inicio = fila;
            int contador = 1;

            while (fila + contador < filas)
            {
                int siguiente =
                    (fila + contador) * columnas + columna;

                int siguienteFicha =
                    obtenerFicha(tablero, siguiente);

                if (siguienteFicha == ficha)
                    contador++;
                else
                    break;
            }

            if (contador >= 3)
            {
                combinaciones++;
                encontro = true;

                for (int i = 0; i < contador; i++)
                {
                    int posicionEliminar =
                        (inicio + i) * columnas + columna;

                    eliminados[posicionEliminar] = true;
                }
            }

            fila = inicio + contador;
        }
    }

    return encontro;
}

void eliminarCombinaciones(unsigned char* tablero,
                           int filas,
                           int columnas,
                           bool* eliminados)
{
    int posiciones = filas * columnas;

    for (int i = 0; i < posiciones; i++)
    {
        if (eliminados[i])
            ponerFicha(tablero, i, 0);
    }
}

void aplicarGravedad(unsigned char* tablero,
                     int filas,
                     int columnas)
{
    for (int columna = 0; columna < columnas; columna++)
    {
        int posicionAbajo = filas - 1;

        for (int fila = filas - 1; fila >= 0; fila--)
        {
            int posicion = fila * columnas + columna;
            int ficha = obtenerFicha(tablero, posicion);

            if (ficha != 0)
            {
                int posicionDestino =
                    posicionAbajo * columnas + columna;

                ponerFicha(tablero,
                           posicionDestino,
                           ficha);

                if (posicionDestino != posicion)
                    ponerFicha(tablero, posicion, 0);

                posicionAbajo--;
            }
        }
    }
}

void generarNuevosFichas(unsigned char* tablero,
                         int filas,
                         int columnas)
{
    int posiciones = filas * columnas;

    for (int i = 0; i < posiciones; i++)
    {
        if (obtenerFicha(tablero, i) == 0)
        {
            int nuevoFicha = rand() % 6 + 1;
            ponerFicha(tablero, i, nuevoFicha);
        }
    }
}

int procesarCascadas(unsigned char* tablero,
                     int filas,
                     int columnas,
                     int& totalEliminados,
                     int& totalCombinaciones,
                     int& puntaje)
{
    int posiciones = filas * columnas;
    int numeroCascadas = 0;

    bool* eliminados = new bool[posiciones];
    bool encontro = true;

    while (encontro)
    {
        for (int i = 0; i < posiciones; i++)
            eliminados[i] = false;

        int combinaciones = 0;

        encontro = detectarCombinaciones(
            tablero,
            filas,
            columnas,
            eliminados,
            combinaciones
            );

        if (encontro)
        {
            int cantidadEliminados = 0;

            for (int i = 0; i < posiciones; i++)
            {
                if (eliminados[i])
                    cantidadEliminados++;
            }

            eliminarCombinaciones(
                tablero, filas, columnas, eliminados
                );

            aplicarGravedad(tablero, filas, columnas);
            generarNuevosFichas(tablero, filas, columnas);

            totalEliminados += cantidadEliminados;
            totalCombinaciones += combinaciones;
            puntaje += cantidadEliminados * 10;

            numeroCascadas++;
        }
    }

    delete[] eliminados;

    return numeroCascadas;
}

void llenarTableroAleatorio(unsigned char* tablero,
                            int filas,
                            int columnas)
{
    int posiciones = filas * columnas;

    for (int i = 0; i < posiciones; i++)
    {
        int ficha = rand() % 6 + 1;
        ponerFicha(tablero, i, ficha);
    }
}

int pedirPosicion(int filas, int columnas)
{
    int fila;
    int columna;

    cout << "Ingrese la fila: ";
    cin >> fila;

    cout << "Ingrese la columna: ";
    cin >> columna;

    while (fila < 0 || fila >= filas ||
           columna < 0 || columna >= columnas)
    {
        cout << "Posicion no valida." << endl;

        cout << "Ingrese la fila: ";
        cin >> fila;

        cout << "Ingrese la columna: ";
        cin >> columna;
    }

    return fila * columnas + columna;
}

