#include <iostream>
#include <vector>
#include <string>
#include <fstream>  // Para manejo de archivos
#include <limits>   // Para std::numeric_limits
#include <cstring>  // Para strcpy, strncpy
#include <iomanip>  // Para std::setw, std::left

const char* NOMBRE_ARCHIVO = "notas.dat";
const int MAX_NOMBRE = 50; // Máximo de caracteres para nombres/apellidos
const int MAX_RESULTADO = 10; // "Aprobó" / "Reprobó"

// --- Estructura con arreglos de char para compatibilidad binaria ---
struct Estudiante {
    int id;
    char nombre[MAX_NOMBRE + 1];     // +1 para el carácter nulo '\0'
    char apellido[MAX_NOMBRE + 1];
    double nota1;
    double nota2;
    double nota3;
    double nota4;
    double promedio;
    char resultado[MAX_RESULTADO + 1]; // "Aprobó" o "Reprobó"
};

// --- Prototipos de Funciones CRUD y Auxiliares ---
void mostrarMenu();
void crearEstudiante(std::vector<Estudiante>& db);
void leerEstudiantes(const std::vector<Estudiante>& db);
void actualizarEstudiante(std::vector<Estudiante>& db);
void eliminarEstudiante(std::vector<Estudiante>& db);
int buscarEstudiantePorId(const std::vector<Estudiante>& db, int idBuscado);
void calcularResultadoEstudiante(Estudiante& est); // Calcula promedio y resultado
bool guardarArchivo(const std::vector<Estudiante>& db);
bool cargarArchivo(std::vector<Estudiante>& db);

// Funciones auxiliares de lectura (adaptadas para char[])
double leerDouble(const std::string& mensaje);
int leerInt(const std::string& mensaje);
void leerCadena(const std::string& mensaje, char* destino, int maxLen);


// --- Función Principal ---
int main() {
    std::vector<Estudiante> baseDeDatos;
    int opcion;

    std::cout << "--- Programa de Notas CRUD (Archivos Binarios) ---\n";

    // Cargar datos existentes al iniciar
    if (!cargarArchivo(baseDeDatos)) {
        std::cout << "Advertencia: No se pudo cargar 'notas.dat' o el archivo no existe aún.\n";
    } else {
         std::cout << "Datos cargados desde '" << NOMBRE_ARCHIVO << "'\n";
    }


    do {
        mostrarMenu();
        opcion = leerInt("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                crearEstudiante(baseDeDatos);
                break;
            case 2:
                leerEstudiantes(baseDeDatos);
                break;
            case 3:
                actualizarEstudiante(baseDeDatos);
                break;
            case 4:
                eliminarEstudiante(baseDeDatos);
                break;
            case 5:
                if (guardarArchivo(baseDeDatos)) {
                    std::cout << "Datos guardados correctamente en '" << NOMBRE_ARCHIVO << "'.\n";
                } else {
                    std::cerr << "Error al guardar los datos.\n";
                }
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
        std::cout << std::endl; // Espacio entre operaciones

    } while (opcion != 5);

    return 0;
}

// --- Implementación de Funciones ---

void mostrarMenu() {
    std::cout << "\n--- MENÚ ---\n";
    std::cout << "1. Crear Estudiante (Agregar)\n";
    std::cout << "2. Leer Estudiantes (Mostrar Todos)\n";
    std::cout << "3. Actualizar Estudiante\n";
    std::cout << "4. Eliminar Estudiante\n";
    std::cout << "5. Guardar y Salir\n";
    std::cout << "------------\n";
}

void calcularResultadoEstudiante(Estudiante& est) {
    est.promedio = (est.nota1 + est.nota2 + est.nota3 + est.nota4) / 4.0;
    if (est.promedio >= 60.0) {
        strncpy(est.resultado, "Aprobó", MAX_RESULTADO);
    } else {
        strncpy(est.resultado, "Reprobó", MAX_RESULTADO);
    }
    est.resultado[MAX_RESULTADO] = '\0'; // Asegurar terminación nula
}

void crearEstudiante(std::vector<Estudiante>& db) {
    std::cout << "\n--- Crear Nuevo Estudiante ---\n";
    Estudiante nuevo;
    nuevo.id = leerInt("ID: ");

    // Verificar si el ID ya existe
    if (buscarEstudiantePorId(db, nuevo.id) != -1) {
        std::cout << "Error: El ID " << nuevo.id << " ya existe.\n";
        return;
    }

    leerCadena("Nombres: ", nuevo.nombre, MAX_NOMBRE);
    leerCadena("Apellidos: ", nuevo.apellido, MAX_NOMBRE);
    nuevo.nota1 = leerDouble("Nota 1: ");
    nuevo.nota2 = leerDouble("Nota 2: ");
    nuevo.nota3 = leerDouble("Nota 3: ");
    nuevo.nota4 = leerDouble("Nota 4: ");

    calcularResultadoEstudiante(nuevo); // Calcular promedio y resultado

    db.push_back(nuevo); // Agregar al vector en memoria
    std::cout << "Estudiante agregado correctamente.\n";
}

void leerEstudiantes(const std::vector<Estudiante>& db) {
    std::cout << "\n--- Lista de Estudiantes ---\n";
    if (db.empty()) {
        std::cout << "No hay estudiantes registrados.\n";
        return;
    }

    std::cout << std::left; // Alinear a la izquierda
    std::cout << std::setw(6) << "ID"
              << std::setw(MAX_NOMBRE + 1) << "Nombres"
              << std::setw(MAX_NOMBRE + 1) << "Apellidos"
              << std::setw(10) << "Promedio"
              << std::setw(MAX_RESULTADO + 1) << "Resultado" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------\n"; // Línea separadora

    std::cout.precision(2);
    for (const auto& est : db) {
        std::cout << std::setw(6) << est.id
                  << std::setw(MAX_NOMBRE + 1) << est.nombre
                  << std::setw(MAX_NOMBRE + 1) << est.apellido
                  << std::setw(10) << std::fixed << est.promedio
                  << std::setw(MAX_RESULTADO + 1) << est.resultado << std::endl;
    }
     std::cout << "----------------------------------------------------------------------------------------------------\n";
}

int buscarEstudiantePorId(const std::vector<Estudiante>& db, int idBuscado) {
    for (int i = 0; i < db.size(); ++i) {
        if (db[i].id == idBuscado) {
            return i; // Retorna el índice si lo encuentra
        }
    }
    return -1; // Retorna -1 si no lo encuentra
}


void actualizarEstudiante(std::vector<Estudiante>& db) {
    std::cout << "\n--- Actualizar Estudiante ---\n";
    if (db.empty()) {
        std::cout << "No hay estudiantes para actualizar.\n";
        return;
    }
    int idBuscar = leerInt("Ingrese el ID del estudiante a actualizar: ");
    int indice = buscarEstudiantePorId(db, idBuscar);

    if (indice == -1) {
        std::cout << "Estudiante con ID " << idBuscar << " no encontrado.\n";
        return;
    }

    std::cout << "Estudiante encontrado. Ingrese los nuevos datos (deje en blanco para no cambiar texto):\n";
    Estudiante& est = db[indice]; // Obtener referencia al estudiante

    // Pedir nuevos datos (solo actualiza si se ingresa algo)
    char buffer[MAX_NOMBRE + 1];

    leerCadena("Nuevos Nombres: ", buffer, MAX_NOMBRE);
    if (strlen(buffer) > 0) strncpy(est.nombre, buffer, MAX_NOMBRE);

    leerCadena("Nuevos Apellidos: ", buffer, MAX_NOMBRE);
     if (strlen(buffer) > 0) strncpy(est.apellido, buffer, MAX_NOMBRE);

    // Para las notas, podríamos pedir confirmación o directamente el nuevo valor
    std::cout << "Nota 1 actual: " << est.nota1 << ". Nuevo valor: ";
    est.nota1 = leerDouble("");
    std::cout << "Nota 2 actual: " << est.nota2 << ". Nuevo valor: ";
    est.nota2 = leerDouble("");
    std::cout << "Nota 3 actual: " << est.nota3 << ". Nuevo valor: ";
    est.nota3 = leerDouble("");
    std::cout << "Nota 4 actual: " << est.nota4 << ". Nuevo valor: ";
    est.nota4 = leerDouble("");


    calcularResultadoEstudiante(est); // Recalcular con las nuevas notas

    std::cout << "Estudiante actualizado correctamente.\n";
}

void eliminarEstudiante(std::vector<Estudiante>& db) {
     std::cout << "\n--- Eliminar Estudiante ---\n";
     if (db.empty()) {
        std::cout << "No hay estudiantes para eliminar.\n";
        return;
    }
    int idBuscar = leerInt("Ingrese el ID del estudiante a eliminar: ");
    int indice = buscarEstudiantePorId(db, idBuscar);

    if (indice == -1) {
        std::cout << "Estudiante con ID " << idBuscar << " no encontrado.\n";
        return;
    }

    std::cout << "Estudiante: " << db[indice].nombre << " " << db[indice].apellido << std::endl;
    char confirmacion;
    std::cout << "¿Está seguro de que desea eliminar este estudiante? (s/n): ";
    std::cin >> confirmacion;
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

    if (confirmacion == 's' || confirmacion == 'S') {
        db.erase(db.begin() + indice); // Eliminar el elemento del vector
        std::cout << "Estudiante eliminado correctamente.\n";
    } else {
        std::cout << "Eliminación cancelada.\n";
    }
}


bool guardarArchivo(const std::vector<Estudiante>& db) {
    // Abrir en modo binario y truncar (sobrescribir si existe)
    std::ofstream archivo(NOMBRE_ARCHIVO, std::ios::binary | std::ios::trunc);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo '" << NOMBRE_ARCHIVO << "' para escritura.\n";
        return false;
    }

    // Escribir cada estructura del vector al archivo
    for (const auto& est : db) {
        archivo.write(reinterpret_cast<const char*>(&est), sizeof(Estudiante));
         if (!archivo.good()) {
             std::cerr << "Error al escribir estudiante con ID " << est.id << " en el archivo.\n";
             archivo.close();
             return false;
         }
    }

    archivo.close();
    return archivo.good(); // Verifica si hubo errores al final
}

bool cargarArchivo(std::vector<Estudiante>& db) {
    // Abrir en modo binario para lectura
    std::ifstream archivo(NOMBRE_ARCHIVO, std::ios::binary);
    if (!archivo.is_open()) {
        // No es necesariamente un error si el archivo no existe la primera vez
        return false;
    }

    db.clear(); // Limpiar el vector actual antes de cargar
    Estudiante temp;

    // Leer estructuras del archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&temp), sizeof(Estudiante))) {
         if (archivo.gcount() == sizeof(Estudiante)) { // Asegurarse que se leyó el tamaño completo
             db.push_back(temp);
         } else if (!archivo.eof()) {
             // Si no se leyó el tamaño completo y no es fin de archivo, hubo error
             std::cerr << "Error al leer datos del archivo (posible corrupción).\n";
             archivo.close();
             return false;
         }
    }

    archivo.close();
    // Verifica si el error final fue solo EOF (End Of File), lo cual es normal
    return archivo.eof();
}

// --- Funciones Auxiliares de Lectura ---
double leerDouble(const std::string& mensaje) {
    double valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        } else {
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int leerInt(const std::string& mensaje) {
     int valor;
     while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.good()) {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        } else {
            std::cout << "Entrada inválida. Por favor ingrese un número entero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Lee una cadena y la guarda en un char[], asegurando terminación nula
void leerCadena(const std::string& mensaje, char* destino, int maxLen) {
    std::cout << mensaje;
    std::string temp;
    std::getline(std::cin, temp);
    // Copia de forma segura, truncando si es necesario y asegurando el nulo
    strncpy(destino, temp.c_str(), maxLen);
    destino[maxLen] = '\0'; // Asegurar terminación nula
}
