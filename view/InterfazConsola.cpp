#include "InterfazConsola.h"
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <stdlib.h>
#endif

void InterfazConsola::mostrarTitulo(const std::string& titulo) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "   " << titulo << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void InterfazConsola::mostrarMensaje(const std::string& mensaje) {
    std::cout << "> " << mensaje << std::endl;
}

void InterfazConsola::mostrarError(const std::string& error) {
    std::cout << "❌ ERROR: " << error << std::endl;
}

void InterfazConsola::mostrarExito(const std::string& exito) {
    std::cout << "✅ " << exito << std::endl;
}

void InterfazConsola::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void InterfazConsola::pausa() {
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

std::string InterfazConsola::leerComando() {
    std::cout << "\nCOMANDO > ";
    std::string comando;
    std::getline(std::cin, comando);
    return comando;
}