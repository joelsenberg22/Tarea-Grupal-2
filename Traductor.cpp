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

// Funci�n para cargar palabras del archivo
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

// Funci�n para guardar palabras al archivo
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