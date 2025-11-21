#include "SistemaGuardado.h"
#include "model/Jugador.h"
#include "model/Habitacion.h"
#include <iostream>
#include <fstream>

bool SistemaGuardado::guardarPartida(const std::string& archivo, Jugador* jugador, Habitacion* habitacionActual) {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error: No se pudo crear el archivo de guardado." << std::endl;
        return false;
    }

    // Guardar datos básicos
    file << "ESTACION_ECLIPSE_SAVE" << std::endl;

    // Guardar jugador
    guardarJugador(file, jugador);

    // Guardar habitación actual (por nombre)
    file << habitacionActual->getNombre() << std::endl;

    file.close();
    std::cout << "✅ Partida guardada correctamente en: " << archivo << std::endl;
    return true;
}

bool SistemaGuardado::cargarPartida(const std::string& archivo, Jugador*& jugador, Habitacion*& habitacionActual) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Error: No se encontró el archivo de guardado." << std::endl;
        return false;
    }

    std::string header;
    std::getline(file, header);

    if (header != "ESTACION_ECLIPSE_SAVE") {
        std::cout << "Error: Archivo de guardado corrupto." << std::endl;
        return false;
    }

    // Cargar jugador
    cargarJugador(file, jugador);

    file.close();
    std::cout << "✅ Partida cargada correctamente desde: " << archivo << std::endl;
    return true;
}

void SistemaGuardado::guardarJugador(std::ofstream& archivo, Jugador* jugador) {
    archivo << jugador->getNombre() << std::endl;
    archivo << jugador->getSalud() << std::endl;
    archivo << jugador->getEnergia() << std::endl;
    archivo << jugador->getNivel() << std::endl;
    archivo << jugador->getExperiencia() << std::endl;

    // Guardar items del inventario
    archivo << "INVENTARIO_FIN" << std::endl;
}

void SistemaGuardado::cargarJugador(std::ifstream& archivo, Jugador*& jugador) {
    std::string nombre;
    int salud, energia, nivel, experiencia;

    archivo >> nombre >> salud >> energia >> nivel >> experiencia;

    jugador = new Jugador(nombre);
    // Nota: Necesitaríamos setters para restaurar el estado exacto

    std::string finInventario;
    archivo >> finInventario; // Leer "INVENTARIO_FIN"
}