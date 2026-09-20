#include <iostream>
#include "tablero.h"

using namespace std;

int calcularBytes(int filas, int columnas)
{
    int posiciones = filas * columnas;
    int bits = posiciones * 3;
    int bytes = bits / 8;

    if (bits % 8 != 0)
        bytes++;

    return bytes;
}

unsigned char* crearTablero(int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes];

    for (int i = 0; i < bytes; i++)
        tablero[i] = 0;

    return tablero;
}

int obtenerFicha(unsigned char* tablero, int posicion)
{
    int bitInicio = posicion * 3;
    int numeroByte = bitInicio / 8;
    int desplazamiento = bitInicio % 8;

    if (desplazamiento + 3 <= 8)
    {
        return (tablero[numeroByte] >> desplazamiento) & 7;
    }

    int bitsPrimerByte = 8 - desplazamiento;
    int bitsSegundoByte = 3 - bitsPrimerByte;

    int mascaraPrimerByte = (1 << bitsPrimerByte) - 1;
    int mascaraSegundoByte = (1 << bitsSegundoByte) - 1;

    int parte1 = (tablero[numeroByte] >> desplazamiento)
                 & mascaraPrimerByte;

    int parte2 = tablero[numeroByte + 1]
                 & mascaraSegundoByte;

    return parte1 | (parte2 << bitsPrimerByte);
}

void ponerFicha(unsigned char* tablero, int posicion, int ficha)
{
    int bitInicio = posicion * 3;
    int numeroByte = bitInicio / 8;
    int desplazamiento = bitInicio % 8;

    if (desplazamiento + 3 <= 8)
    {
        int mascara = 7 << desplazamiento;

        tablero[numeroByte] =
            tablero[numeroByte] & ~mascara;

        tablero[numeroByte] =
            tablero[numeroByte] |
            ((ficha & 7) << desplazamiento);
    }
    else
    {
        int bitsPrimerByte = 8 - desplazamiento;
        int bitsSegundoByte = 3 - bitsPrimerByte;

        int mascaraPrimerByte = (1 << bitsPrimerByte) - 1;
        int mascaraSegundoByte = (1 << bitsSegundoByte) - 1;

        tablero[numeroByte] =
            tablero[numeroByte] &
            ~(mascaraPrimerByte << desplazamiento);

        tablero[numeroByte] =
            tablero[numeroByte] |
            ((ficha & mascaraPrimerByte)
             << desplazamiento);

        tablero[numeroByte + 1] =
            tablero[numeroByte + 1] &
            ~mascaraSegundoByte;

        tablero[numeroByte + 1] =
            tablero[numeroByte + 1] |
            ((ficha >> bitsPrimerByte)
             & mascaraSegundoByte);
    }
}

void mostrarTablero(unsigned char* tablero, int filas, int columnas)
{
    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            int posicion = fila * columnas + columna;
            int ficha = obtenerFicha(tablero, posicion);

            if (ficha == 0)
            {
                cout << "V ";
            }
            else if (ficha == 7)
            {
                cout << "R ";
            }
            else
            {
                cout << char('A' + ficha - 1) << " ";
            }
        }

        cout << endl;
    }
}
void mostrarBits(unsigned char* tablero, int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);

    cout << "Bits del tablero:" << endl;

    for (int i = 0; i < bytes; i++)
    {
        for (int bit = 0; bit < 8; bit++)
            cout << ((tablero[i] >> bit) & 1);

        cout << " ";
    }

    cout << endl;
}

void mostrarFichasBinario(unsigned char* tablero,
                          int filas,
                          int columnas)
{
    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            int posicion = fila * columnas + columna;
            int ficha = obtenerFicha(tablero, posicion);

            for (int bit = 2; bit >= 0; bit--)
                cout << ((ficha>> bit) & 1);

            cout << " ";
        }

        cout << endl;
    }
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}