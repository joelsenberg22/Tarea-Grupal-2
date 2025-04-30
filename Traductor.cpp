#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Estructura para almacenar cada palabra
struct Palabra {
    string traduccion;
    string funcionalidad;
};

// Mapa global de palabras
map<string, Palabra> diccionario;

// Ruta del archivo donde se guardan las palabras
const string archivoDiccionario = "diccionario.txt";

void limpiarConsola() {
    system("cls"); 
}

// Funciï¿½n para cargar palabras del archivo
void cargarDiccionario() {
    diccionario.clear();
	ifstream archivo(archivoDiccionario.c_str());
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;

        getline(ss, palabra, '|');
        getline(ss, traduccion, '|');
        getline(ss, funcionalidad, '|');

        diccionario[palabra] = {traduccion, funcionalidad};
    }
    archivo.close();
}

// Funciï¿½n para guardar palabras al archivo
void guardarDiccionario() {
    ofstream archivo(archivoDiccionario.c_str(), ios::trunc);  // Truncar el archivo antes de escribir
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }
    
    for (map<string, Palabra>::iterator it = diccionario.begin(); it != diccionario.end(); ++it) {
        archivo << it->first << "|" << it->second.traduccion << "|" << it->second.funcionalidad << "\n";
    }
    archivo.close();
}
// CRUD
void agregarPalabra() {
    string palabra, traduccion, funcionalidad;
    cout << "Ingrese Palabra: ";
    cin >> palabra;
    cout << "Ingrese Traduccion: ";
    cin.ignore();
    getline(cin, traduccion);
    cout << "Ingrese Funcionalidad: ";
    getline(cin, funcionalidad);

    diccionario[palabra] = {traduccion, funcionalidad};
    guardarDiccionario();
    cout << "Palabra agregada correctamente.\n";
}

void mostrarDiccionario() {
    cout << "\nListado de Palabras:\n";
   for (map<string, Palabra>::iterator it = diccionario.begin(); it != diccionario.end(); ++it) {
    cout << "Palabra: " << it->first 
         << ", Traduccion: " << it->second.traduccion
         << ", Funcionalidad: " << it->second.funcionalidad << endl;
}

}
void actualizarPalabra() {
    string palabra;
    cout << "Ingrese la palabra a actualizar: ";
    cin >> palabra;

    // Convertir la palabra ingresada a minúsculas
    for (size_t i = 0; i < palabra.length(); ++i) {
        palabra[i] = tolower(palabra[i]);
    }
    
    map<string, Palabra>::iterator it = diccionario.find(palabra);
    
    if (it != diccionario.end()) {
        cout << "Nueva Traduccion: ";
        cin.ignore();  // Limpiar el buffer de entrada
        getline(cin, it->second.traduccion);
        cout << "Nueva Funcionalidad: ";
        getline(cin, it->second.funcionalidad);
        guardarDiccionario();
        cout << "Palabra actualizada.\n";
    } else {
        cout << "Palabra no encontrada.\n";
    }
}

void eliminarPalabra() {
    string palabra;
    cout << "Ingrese la palabra a eliminar: ";
    cin >> palabra;
    if (diccionario.erase(palabra)) {
        guardarDiccionario();
        cout << "Palabra eliminada.\n";
    } else {
        cout << "Palabra no encontrada.\n";
    }
}
void traducirCodigo() {
    cin.ignore();
    cout << "Ingrese el codigo C++ (finalice con una linea que contenga solo 'FIN'):\n";
    vector<string> codigoOriginal;
    string linea;
    
    // Lectura de código hasta encontrar "fin"
    while (getline(cin, linea)) {
        // Convertir la línea a minúsculas antes de cualquier cosa
        for (size_t i = 0; i < linea.length(); ++i) {
            linea[i] = tolower(linea[i]);
        }

        if (linea == "fin") break; // terminamos la lectura al encontrar "fin"
        codigoOriginal.push_back(linea);
    }

    cout << "\n=== Codigo Traducido ===\n";

    // Procesar y traducir el código línea por línea
    bool dentroIfElse = false;
    for (size_t i = 0; i < codigoOriginal.size(); ++i) {
        string linea = codigoOriginal[i];
        stringstream ss(linea);
        string palabra;

        // Detectar las estructuras de control e imprimir la traducción
        bool esEstructura = false;

        while (ss >> palabra) {
            string palabraOriginal = palabra;

            // Quitar paréntesis y signos si hay
            string limpio;
            for (size_t j = 0; j < palabra.length(); ++j) {
                if (isalnum(palabra[j])) limpio += palabra[j];
            }

            // Buscar traducción en el diccionario
            if (diccionario.find(limpio) != diccionario.end()) {
                cout << diccionario[limpio].traduccion;
            } else {
                cout << palabraOriginal;
            }
            cout << " ";

            // Detectar las estructuras de control
            if (linea.find("if") != string::npos) {
                esEstructura = true;
                if (dentroIfElse == false) {
                    cout << "inicio si ";
                    dentroIfElse = true;
                }
            } else if (linea.find("else") != string::npos) {
                esEstructura = true;
                if (dentroIfElse) {
                    cout << "fin si ";
                }
                cout << "inicio entonces ";
                dentroIfElse = true;
            }
        }

        // Imprimir el cierre de estructuras
        size_t posFin = linea.find('}');  // Buscar fin de llave
        if (posFin != string::npos) {
            if (dentroIfElse) {
                if (linea.find("if") != string::npos) {
                    cout << "fin si ";
                } else if (linea.find("else") != string::npos) {
                    cout << "fin entonces ";
                }
                dentroIfElse = false;
            }
        }

        cout << endl;
    }
}


// Menú principal
void menu() {
    int opcion;
    do {
        cout << "\n--- Proyecto Traductor ---\n";
        cout << "1. Agregar palabra\n";
        cout << "2. Mostrar palabras\n";
        cout << "3. Actualizar palabra\n";
        cout << "4. Eliminar palabra\n";
        cout << "5. Traducir Codigo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: limpiarConsola(); agregarPalabra(); break;
            case 2: limpiarConsola(); mostrarDiccionario(); break;
            case 3: limpiarConsola(); actualizarPalabra(); break;
            case 4: limpiarConsola(); eliminarPalabra(); break;
            case 5: limpiarConsola(); traducirCodigo(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n"; break;
            
        }
    } while (opcion != 0);
}



// Programa principal
int main() {
    cargarDiccionario();
    menu();
    return 0;
}
