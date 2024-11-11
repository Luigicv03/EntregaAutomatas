#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "./matrix.h"

using namespace std;

// Función para obtener el índice correspondiente a un carácter
int obtenerIndice(char simbolo)
{
    switch (simbolo)
    {
    case 'P':
        return 0;
    case 'L':
        return 1;
    case 'A':
        return 2;
    case 'Z':
        return 3;
    case 'O':
        return 4;
    default:
        return -1; // Retorna -1 si el carácter no es válido
    }
}

// Función principal
int main()
{
    // Intentamos abrir el archivo de entrada
    ifstream archivoEntrada("text.txt");
    if (!archivoEntrada.is_open())
    {
        cout << "Error: archivo no encontrado." << endl;
        return 501;
    }

    string linea;
    vector<string> lineasValidas;
    vector<string> lineasInvalidas;

    // Procesamos cada línea del archivo
    while (getline(archivoEntrada, linea))
    {
        int estadoActual = 0;
        bool esValida = true;

        // Recorremos cada carácter de la línea
        for (char simbolo : linea)
        {
            int indice = obtenerIndice(simbolo);
            // Si el índice es inválido o la transición no existe en la matriz, marcamos la línea como inválida
            if (indice == -1 || matrix[estadoActual][indice] == -1)
            {
                esValida = false;
                break;  // Interrumpimos el procesamiento de esta línea
            }
            // Actualizamos el estado según la transición
            estadoActual = matrix[estadoActual][indice];

            // Si llegamos al estado de aceptación, terminamos la validación
            if (estadoActual == 3)
            {
                break;
            }
        }

        // Si la línea es válida y termina en el estado de aceptación (estado 3), la agregamos a las válidas
        if (esValida && estadoActual == 3)
        {
            lineasValidas.push_back(linea);
        }
        else
        {
            lineasInvalidas.push_back(linea);
        }
    }

    // Mostramos las líneas válidas e inválidas
    cout << "Cadenas validas: ";
    for (const string &lineaValida : lineasValidas)
    {
        cout << lineaValida << " ";
    }
    cout << endl;

    cout << "Cadenas invalidas: ";
    for (const string &lineaInvalida : lineasInvalidas)
    {
        cout << lineaInvalida << " ";
    }
    cout << endl;

    return 0;
}
