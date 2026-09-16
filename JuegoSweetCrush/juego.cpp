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

void generarNuevasFichas(unsigned char* tablero,
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
            generarNuevasFichas(tablero, filas, columnas);

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

void guardarNuevoTablero(unsigned char*& tablero,
                         unsigned char* nuevoTablero,
                         int nuevasFilas,
                         int nuevasColumnas,
                         int& bytesAsignados,
                         bool eliminar)
{
    int bytesNecesarios =
        calcularBytes(nuevasFilas, nuevasColumnas);

    bool cambiarMemoria = false;

    if (bytesNecesarios > bytesAsignados)
    {
        cambiarMemoria = true;
    }
    else if (eliminar)
    {
        int bitsUtilizados =
            nuevasFilas * nuevasColumnas * 3;

        int bitsReservados =
            bytesAsignados * 8;

        double utilizacion =
            (bitsUtilizados * 100.0) / bitsReservados;

        if (utilizacion < 65.0)
            cambiarMemoria = true;
    }

    if (cambiarMemoria)
    {
        delete[] tablero;

        tablero =
            new unsigned char[bytesNecesarios];

        for (int i = 0; i < bytesNecesarios; i++)
            tablero[i] = nuevoTablero[i];

        bytesAsignados = bytesNecesarios;
    }
    else
    {
        for (int i = 0; i < bytesAsignados; i++)
            tablero[i] = 0;

        for (int i = 0; i < bytesNecesarios; i++)
            tablero[i] = nuevoTablero[i];
    }

    delete[] nuevoTablero;
}

void agregarFila(unsigned char*& tablero,
                 int& filas,
                 int columnas,
                 int posicionFila,
                 int& bytesAsignados)
{
    int nuevasFilas = filas + 1;

    unsigned char* nuevoTablero =
        crearTablero(nuevasFilas, columnas);

    for (int fila = 0; fila < nuevasFilas; fila++)
    {
        if (fila == posicionFila)
        {
            for (int columna = 0; columna < columnas; columna++)
            {
                int posicion =
                    fila * columnas + columna;

                ponerFicha(
                    nuevoTablero,
                    posicion,
                    rand() % 6 + 1
                    );
            }
        }
        else
        {
            int filaVieja;

            if (fila < posicionFila)
                filaVieja = fila;
            else
                filaVieja = fila - 1;

            for (int columna = 0;
                 columna < columnas;
                 columna++)
            {
                int posicionVieja =
                    filaVieja * columnas + columna;

                int posicionNueva =
                    fila * columnas + columna;

                int ficha =
                    obtenerFicha(
                        tablero,
                        posicionVieja
                        );

                ponerFicha(
                    nuevoTablero,
                    posicionNueva,
                    ficha
                    );
            }
        }
    }

    guardarNuevoTablero(
        tablero,
        nuevoTablero,
        nuevasFilas,
        columnas,
        bytesAsignados,
        false
        );

    filas = nuevasFilas;
}

void eliminarFila(unsigned char*& tablero,
                  int& filas,
                  int columnas,
                  int posicionFila,
                  int& bytesAsignados)
{
    if (filas <= 1)
        return;

    int nuevasFilas = filas - 1;

    unsigned char* nuevoTablero =
        crearTablero(nuevasFilas, columnas);

    for (int fila = 0; fila < filas; fila++)
    {
        if (fila == posicionFila)
            continue;

        int nuevaFila;

        if (fila < posicionFila)
            nuevaFila = fila;
        else
            nuevaFila = fila - 1;

        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            int posicionVieja =
                fila * columnas + columna;

            int posicionNueva =
                nuevaFila * columnas + columna;

            int ficha =
                obtenerFicha(
                    tablero,
                    posicionVieja
                    );

            ponerFicha(
                nuevoTablero,
                posicionNueva,
                ficha
                );
        }
    }

    guardarNuevoTablero(
        tablero,
        nuevoTablero,
        nuevasFilas,
        columnas,
        bytesAsignados,
        true
        );

    filas = nuevasFilas;
}

void agregarColumna(unsigned char*& tablero,
                    int filas,
                    int& columnas,
                    int posicionColumna,
                    int& bytesAsignados)
{
    int nuevasColumnas = columnas + 1;

    unsigned char* nuevoTablero =
        crearTablero(filas, nuevasColumnas);

    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0;
             columna < nuevasColumnas;
             columna++)
        {
            int posicionNueva =
                fila * nuevasColumnas + columna;

            if (columna == posicionColumna)
            {
                ponerFicha(
                    nuevoTablero,
                    posicionNueva,
                    rand() % 6 + 1
                    );
            }
            else
            {
                int columnaVieja;

                if (columna < posicionColumna)
                    columnaVieja = columna;
                else
                    columnaVieja = columna - 1;

                int posicionVieja =
                    fila * columnas + columnaVieja;

                int ficha =
                    obtenerFicha(
                        tablero,
                        posicionVieja
                        );

                ponerFicha(
                    nuevoTablero,
                    posicionNueva,
                    ficha
                    );
            }
        }
    }

    guardarNuevoTablero(
        tablero,
        nuevoTablero,
        filas,
        nuevasColumnas,
        bytesAsignados,
        false
        );

    columnas = nuevasColumnas;
}

void eliminarColumna(unsigned char*& tablero,
                     int filas,
                     int& columnas,
                     int posicionColumna,
                     int& bytesAsignados)
{
    if (columnas <= 1)
        return;

    int nuevasColumnas = columnas - 1;

    unsigned char* nuevoTablero =
        crearTablero(filas, nuevasColumnas);

    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            if (columna == posicionColumna)
                continue;

            int nuevaColumna;

            if (columna < posicionColumna)
                nuevaColumna = columna;
            else
                nuevaColumna = columna - 1;

            int posicionVieja =
                fila * columnas + columna;

            int posicionNueva =
                fila * nuevasColumnas
                + nuevaColumna;

            int ficha =
                obtenerFicha(
                    tablero,
                    posicionVieja
                    );

            ponerFicha(
                nuevoTablero,
                posicionNueva,
                ficha
                );
        }
    }

    guardarNuevoTablero(
        tablero,
        nuevoTablero,
        filas,
        nuevasColumnas,
        bytesAsignados,
        true
        );

    columnas = nuevasColumnas;
}

