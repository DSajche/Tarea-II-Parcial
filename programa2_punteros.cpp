#include <iostream>
#include <string>
#include <vector> // Solo para lectura de línea, no para almacenamiento principal
#include <limits> // Para std::numeric_limits
#include <new>    // Para std::nothrow

// --- Definición de la Estructura ---
struct Estudiante {
    int id;
    std::string nombre;
    std::string apellido;
    double nota1;
    double nota2;
    double nota3;
    double nota4;
    double promedio;
    std::string resultado; // "Aprobó" o "Reprobó"
};

// --- Prototipos de Funciones ---
// Usamos punteros para pasar el arreglo de estructuras
void ingresarEstudiantes(Estudiante* arrEstudiantes, int n);
void calcularResultados(Estudiante* arrEstudiantes, int n);
void mostrarEstudiantes(const Estudiante* arrEstudiantes, int n);

// Funciones auxiliares de lectura (igual que en programa 1)
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

// --- Función Principal ---
int main() {
    int n = 0;
    Estudiante* estudiantes = nullptr; // Puntero al arreglo de estudiantes

    std::cout << "--- Programa de Notas (Punteros y Estructuras) ---\n";
     n = leerInt("Ingrese la cantidad de estudiantes: ");

    if (n <= 0) {
        std::cout << "Cantidad inválida." << std::endl;
        return 1;
    }

    // --- Asignación dinámica de memoria para el arreglo ---
    // Usamos 'new (std::nothrow)' para evitar que lance excepción si falla
    estudiantes = new (std::nothrow) Estudiante[n];

    if (estudiantes == nullptr) {
        std::cerr << "Error: No se pudo asignar memoria para " << n << " estudiantes." << std::endl;
        return 1; // Salir si no hay memoria
    }

    // Llamada a funciones pasando el puntero al arreglo
    ingresarEstudiantes(estudiantes, n);
    calcularResultados(estudiantes, n);
    mostrarEstudiantes(estudiantes, n);

    // --- Liberar la memoria asignada ---
    delete[] estudiantes; // Importante liberar la memoria dinámica
    estudiantes = nullptr; // Buena práctica: poner el puntero a null después de liberar

    return 0;
}

// --- Implementación de Funciones ---

void ingresarEstudiantes(Estudiante* arrEstudiantes, int n) {
    std::cout << "\n--- Ingreso de Datos ---\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "\nEstudiante #" << (i + 1) << ":\n";
        // Acceso a los miembros de la estructura usando el índice del arreglo
        arrEstudiantes[i].id = leerInt("  ID: ");

        std::cout << "  Nombres: ";
        std::getline(std::cin, arrEstudiantes[i].nombre);

        std::cout << "  Apellidos: ";
        std::getline(std::cin, arrEstudiantes[i].apellido);

        arrEstudiantes[i].nota1 = leerDouble("  Nota 1: ");
        arrEstudiantes[i].nota2 = leerDouble("  Nota 2: ");
        arrEstudiantes[i].nota3 = leerDouble("  Nota 3: ");
        arrEstudiantes[i].nota4 = leerDouble("  Nota 4: ");
    }
}

void calcularResultados(Estudiante* arrEstudiantes, int n) {
    for (int i = 0; i < n; ++i) {
        arrEstudiantes[i].promedio = (arrEstudiantes[i].nota1 + arrEstudiantes[i].nota2 +
                                      arrEstudiantes[i].nota3 + arrEstudiantes[i].nota4) / 4.0;
        if (arrEstudiantes[i].promedio >= 60.0) {
            arrEstudiantes[i].resultado = "Aprobó";
        } else {
            arrEstudiantes[i].resultado = "Reprobó";
        }
    }
}

void mostrarEstudiantes(const Estudiante* arrEstudiantes, int n) {
    std::cout << "\n--- Resultados ---\n";
    std::cout.precision(2); // Para mostrar promedio con 2 decimales
    for (int i = 0; i < n; ++i) {
        std::cout << "ID: " << arrEstudiantes[i].id
                  << ", Nombre: " << arrEstudiantes[i].nombre << " " << arrEstudiantes[i].apellido
                  << ", Promedio: " << std::fixed << arrEstudiantes[i].promedio
                  << ", Resultado: " << arrEstudiantes[i].resultado << std::endl;
    }
}
