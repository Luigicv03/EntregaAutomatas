#include<iostream>
#include<fstream>
#include<string>

using namespace std;

string word = ""; // almacenamiento de la expresión válida

/* Funciones de estado */
void q0(string&, int&);
void q1(string&, int&);
void q2(string&, int&);
void q3(string&, int&);
void q4(string&, int&);
void q5(string&, int&);
int AFD(string, int);

int main() {

    ifstream inputFile("text.txt");

    if (!inputFile.is_open()) {
        cout << "No se encontro el archivo" << endl;
        return 501;
    }

    string line = "";

    while (getline(inputFile, line)) { // Obtención de línea de entrada
        bool flag = false;
        int i = 0;

        cout << "Procesando la cadena: " << line << endl;

        while (i < line.length()) {
            word = "";  // Limpiar palabra antes de procesar una nueva

            // Intentamos procesar la cadena con el AFD
            if (AFD(line, i) > 0) {
                cout << word << " es valido" << endl << endl;
            } else {
                flag = true;
                cout << "No es valido: ";
            }

            // Si no es válido, mostramos el error
            if (flag) {
                cout << line.substr(i) << endl << endl;
            }

            // Avanzar al siguiente conjunto de caracteres separados por espacio
            while (i < line.length() && line[i] != ' ') {
                i++;
            }
            i++; // Saltar el espacio
        }
    }

    return 0;
}

// Estado 0: Inicio
void q0(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'V') { // Si es 'V', avanzamos al estado 1
            word += a;
            i++;
            q1(line, i);
        } else if (a == 'B') { // Si es 'B', avanzamos al estado 2
            word += a;
            i++;
            q2(line, i);
        } else {
            throw -1; // Error, carácter no válido
        }
    }
}

// Estado 1: Después de 'V'
void q1(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'A') { // 'A' lleva a estado 2
            word += a;
            i++;
            q2(line, i);
        } else if (a == 'B') { // 'B' lleva al estado 4
            word += a;
            i++;
            q4(line, i);
        } else {
            throw -1; // Error, carácter no válido
        }
    }
}

// Estado 2: Después de 'A' o 'B'
void q2(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'O') { // 'O' vuelve a estado 1
            word += a;
            i++;
            q1(line, i);
        } else if (a == 'V') { // 'V' lleva al estado 3
            word += a;
            i++;
            q3(line, i);
        } else {
            throw -1; // Error, carácter no válido
        }
    }
}

// Estado 3: Después de 'V'
void q3(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'I') { // 'I' repite el estado 3
            word += a;
            i++;
            q3(line, i);
        } else if (a == 'T') { // 'T' lleva al estado 5
            word += a;
            i++;
            q5(line, i);
        } else {
            throw 1; // Error, inesperado en estado 3
        }
    } else {
        cout << "Cadena termina inesperadamente en el estado 3." << endl;
    }
}

// Estado 4: Después de 'B'
void q4(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'I') { // 'I' lleva al estado 3
            word += a;
            i++;
            q3(line, i);
        } else {
            throw 1; // Error, cadena válida termina en estado 4
        }
    } else {
        cout << "Cadena valida termina en el estado 4." << endl;
    }
}

// Estado 5: Después de 'T'
void q5(string& line, int& i) {
    if (i < line.length()) {
        char a = line[i];

        if (a == 'I') { // 'I' lleva al estado 4
            word += a;
            i++;
            q4(line, i);
        } else {
            cout << "Cadena valida termina en el estado 5." << endl;
        }
    } else {
        cout << "Cadena valida termina en el estado 5." << endl;
    }
}

// Función principal del AFD
int AFD(string line, int i) {
    try {
        q0(line, i);
    } catch (int e) {
        return e; // Retorna 1 si válida, -1 si no válida
    }
    return 1;
}
