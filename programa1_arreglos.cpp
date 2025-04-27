#include <iostream>
#include <vector>
#include <string>
#include <numeric> // Para std::accumulate (opcional para promedio)
#include <limits>  // Para std::numeric_limits

// --- Prototipos de Funciones ---
void ingresarEstudiantes(int n,
                        std::vector<int>& ids,
                        std::vector<std::string>& nombres,
                        std::vector<std::string>& apellidos,
                        std::vector<double>& notas1,
                        std::vector<double>& notas2,
                        std::vector<double>& notas3,
                        std::vector<double>& notas4);

void calcularResultados(int n,
                        const std::vector<double>& notas1,
                        const std::vector<double>& notas2,
                        const std::vector<double>& notas3,
                        const std::vector<double>& notas4,
                        std::vector<double>& promedios,
                        std::vector<std::string>& resultados);

void mostrarEstudiantes(int n,
                      const std::vector<int>& ids,
                      const std::vector<std::string>& nombres,
                      const std::vector<std::string>& apellidos,
                      const std::vector<double>& promedios,
                      const std::vector<std::string>& resultados);

// Función auxiliar para limpiar el buffer de entrada y validar números
double leerDouble(const std::string& mensaje) {
    double valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.good()) {
            // Limpiar cualquier caracter extra en la línea (como el Enter)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        } else {
            std::cout << "Entrada inválida. Por favor ingrese un número.\n";
            std::cin.clear(); // Limpiar el estado de error de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
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

    std::cout << "--- Programa de Notas (Vectores) ---\n";
    n = leerInt("Ingrese la cantidad de estudiantes: ");

    if (n <= 0) {
        std::cout << "Cantidad inválida." << std::endl;
        return 1;
    }

    // Declaración de vectores (arreglos dinámicos)
    std::vector<int> ids;
    std::vector<std::string> nombres;
    std::vector<std::string> apellidos;
    std::vector<double> notas1;
    std::vector<double> notas2;
    std::vector<double> notas3;
    std::vector<double> notas4;
    std::vector<double> promedios;
    std::vector<std::string> resultados;

    // Redimensionar vectores para evitar múltiples realocaciones (opcional pero bueno)
    ids.reserve(n);
    nombres.reserve(n);
    apellidos.reserve(n);
    notas1.reserve(n);
    notas2.reserve(n);
    notas3.reserve(n);
    notas4.reserve(n);
    promedios.resize(n); // Necesitan tamaño para asignar en calcularResultados
    resultados.resize(n); // Necesitan tamaño para asignar en calcularResultados


    ingresarEstudiantes(n, ids, nombres, apellidos, notas1, notas2, notas3, notas4);
    calcularResultados(n, notas1, notas2, notas3, notas4, promedios, resultados);
    mostrarEstudiantes(n, ids, nombres, apellidos, promedios, resultados);

    return 0;
}

// --- Implementación de Funciones ---

void ingresarEstudiantes(int n,
                        std::vector<int>& ids,
                        std::vector<std::string>& nombres,
                        std::vector<std::string>& apellidos,
                        std::vector<double>& notas1,
                        std::vector<double>& notas2,
                        std::vector<double>& notas3,
                        std::vector<double>& notas4) {
    std::cout << "\n--- Ingreso de Datos ---\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "\nEstudiante #" << (i + 1) << ":\n";
        ids.push_back(leerInt("  ID: "));

        std::string nombre_temp;
        std::cout << "  Nombres: ";
        std::getline(std::cin, nombre_temp); // Leer línea completa para nombres compuestos
        nombres.push_back(nombre_temp);


        std::string apellido_temp;
        std::cout << "  Apellidos: ";
        std::getline(std::cin, apellido_temp);
        apellidos.push_back(apellido_temp);

        notas1.push_back(leerDouble("  Nota 1: "));
        notas2.push_back(leerDouble("  Nota 2: "));
        notas3.push_back(leerDouble("  Nota 3: "));
        notas4.push_back(leerDouble("  Nota 4: "));
    }
}

void calcularResultados(int n,
                        const std::vector<double>& notas1,
                        const std::vector<double>& notas2,
                        const std::vector<double>& notas3,
                        const std::vector<double>& notas4,
                        std::vector<double>& promedios,
                        std::vector<std::string>& resultados) {
    for (int i = 0; i < n; ++i) {
        promedios[i] = (notas1[i] + notas2[i] + notas3[i] + notas4[i]) / 4.0;
        if (promedios[i] >= 60.0) {
            resultados[i] = "Aprobó";
        } else {
            resultados[i] = "Reprobó";
        }
    }
}

void mostrarEstudiantes(int n,
                      const std::vector<int>& ids,
                      const std::vector<std::string>& nombres,
                      const std::vector<std::string>& apellidos,
                      const std::vector<double>& promedios,
                      const std::vector<std::string>& resultados) {
    std::cout << "\n--- Resultados ---\n";
    std::cout.precision(2); // Para mostrar promedio con 2 decimales
    for (int i = 0; i < n; ++i) {
        std::cout << "ID: " << ids[i]
                  << ", Nombre: " << nombres[i] << " " << apellidos[i]
                  << ", Promedio: " << std::fixed << promedios[i]
                  << ", Resultado: " << resultados[i] << std::endl;
    }
}
