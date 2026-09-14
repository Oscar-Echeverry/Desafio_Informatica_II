#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tablero.h"
#include "juego.h"

using namespace std;

int main()
{
    srand(time(0));

    int filas;
    int columnas;

    cout << "==================================" << endl;
    cout << "          SWEET CRUSH" << endl;
    cout << "==================================" << endl;

    cout << "Ingrese el numero de filas: ";
    cin >> filas;

    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

    while (filas <= 0 || columnas <= 0)
    {
        cout << "Las dimensiones deben ser mayores que 0."
             << endl;

        cout << "Ingrese el numero de filas: ";
        cin >> filas;

        cout << "Ingrese el numero de columnas: ";
        cin >> columnas;
    }

    int bytesAsignados =
        calcularBytes(filas, columnas);

    unsigned char* tablero =
        crearTablero(filas, columnas);

    llenarTableroAleatorio(
        tablero, filas, columnas
        );

    int eliminacionesUsuario = 0;
    int totalEliminados = 0;
    int totalCombinaciones = 0;
    int totalCascadas = 0;
    int puntaje = 0;

    int opcion = -1;

    while (opcion != 0)
    {
        cout << endl;
        cout << "==================================" << endl;
        cout << "              MENU" << endl;
        cout << "==================================" << endl;

        cout << "1. Mostrar tablero" << endl;
        cout << "2. Realizar jugada" << endl;
        cout << "3. Mostrar bits" << endl;
        cout << "4. Mostrar Fichas en binario" << endl;
        cout << "5. Agregar fila" << endl;
        cout << "6. Eliminar fila" << endl;
        cout << "7. Agregar columna" << endl;
        cout << "8. Eliminar columna" << endl;
        cout << "9. Mostrar estadisticas" << endl;
        cout << "0. Salir" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << endl;

        if (opcion == 1)
        {
            cout << "Tablero:" << endl;

            mostrarTablero(
                tablero, filas, columnas
                );
        }
        else if (opcion == 2)
        {
            cout << "Seleccione la ficha que desea eliminar."
                 << endl;

            int posicion =
                pedirPosicion(filas, columnas);

            int ficha =
                obtenerFicha(tablero, posicion);

            if (ficha == 0)
            {
                cout << "La posicion esta vacia."
                     << endl;
            }
            else
            {
                ponerFicha(
                    tablero,
                    posicion,
                    0
                    );

                eliminacionesUsuario++;

                aplicarGravedad(
                    tablero, filas, columnas
                    );

                generarNuevasFichas(
                    tablero, filas, columnas
                    );

                int cascadas =
                    procesarCascadas(
                        tablero,
                        filas,
                        columnas,
                        totalEliminados,
                        totalCombinaciones,
                        puntaje
                        );

                totalCascadas += cascadas;

                cout << "Jugada realizada."
                     << endl;

                cout << "Cascadas generadas: "
                     << cascadas << endl;
            }
        }
        else if (opcion == 3)
        {
            mostrarBits(
                tablero, filas, columnas
                );
        }
        else if (opcion == 4)
        {
            cout << "Fichas en binario:"
                 << endl;

            mostrarFichasBinario(
                tablero, filas, columnas
                );
        }
        else if (opcion == 5)
        {
            int posicionFila;

            cout << "Ingrese la posicion de la nueva fila: ";
            cin >> posicionFila;

            while (posicionFila < 0 ||
                   posicionFila > filas)
            {
                cout << "Posicion no valida."
                     << endl;

                cout << "Ingrese la posicion de la nueva fila: ";
                cin >> posicionFila;
            }

            agregarFila(
                tablero,
                filas,
                columnas,
                posicionFila,
                bytesAsignados
                );

            cout << "Fila agregada correctamente."
                 << endl;
        }
        else if (opcion == 6)
        {
            if (filas <= 1)
            {
                cout << "No se puede eliminar la unica fila."
                     << endl;
            }
            else
            {
                int posicionFila;

                cout << "Ingrese la fila que desea eliminar: ";
                cin >> posicionFila;

                while (posicionFila < 0 ||
                       posicionFila >= filas)
                {
                    cout << "Posicion no valida."
                         << endl;

                    cout << "Ingrese la fila que desea eliminar: ";
                    cin >> posicionFila;
                }

                eliminarFila(
                    tablero,
                    filas,
                    columnas,
                    posicionFila,
                    bytesAsignados
                    );

                cout << "Fila eliminada correctamente."
                     << endl;
            }
        }
        else if (opcion == 7)
        {
            int posicionColumna;

            cout << "Ingrese la posicion de la nueva columna: ";
            cin >> posicionColumna;

            while (posicionColumna < 0 ||
                   posicionColumna > columnas)
            {
                cout << "Posicion no valida."
                     << endl;

                cout << "Ingrese la posicion de la nueva columna: ";
                cin >> posicionColumna;
            }

            agregarColumna(
                tablero,
                filas,
                columnas,
                posicionColumna,
                bytesAsignados
                );

            cout << "Columna agregada correctamente."
                 << endl;
        }
        else if (opcion == 8)
        {
            if (columnas <= 1)
            {
                cout << "No se puede eliminar la unica columna."
                     << endl;
            }
            else
            {
                int posicionColumna;

                cout << "Ingrese la columna que desea eliminar: ";
                cin >> posicionColumna;

                while (posicionColumna < 0 ||
                       posicionColumna >= columnas)
                {
                    cout << "Posicion no valida."
                         << endl;

                    cout << "Ingrese la columna que desea eliminar: ";
                    cin >> posicionColumna;
                }

                eliminarColumna(
                    tablero,
                    filas,
                    columnas,
                    posicionColumna,
                    bytesAsignados
                    );

                cout << "Columna eliminada correctamente."
                     << endl;
            }
        }
        else if (opcion == 9)
        {
            cout << "==================================" << endl;
            cout << "          ESTADISTICAS" << endl;
            cout << "==================================" << endl;

            cout << "Filas actuales: "
                 << filas << endl;

            cout << "Columnas actuales: "
                 << columnas << endl;

            cout << "Bytes asignados: "
                 << bytesAsignados << endl;

            cout << "Eliminaciones del usuario: "
                 << eliminacionesUsuario << endl;

            cout << "Fichas eliminadas: "
                 << totalEliminados << endl;

            cout << "Combinaciones detectadas: "
                 << totalCombinaciones << endl;

            cout << "Cascadas: "
                 << totalCascadas << endl;

            cout << "Puntaje: "
                 << puntaje << endl;
        }
        else if (opcion != 0)
        {
            cout << "Opcion no valida."
                 << endl;
        }
    }

    liberarTablero(tablero);

    cout << endl;
    cout << "Programa finalizado." << endl;

    return 0;
}