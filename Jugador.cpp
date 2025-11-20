#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre)
    : Entidad(nombre, 100), energia(80), nivel(1) {}

void Jugador::atacar(Entidad* objetivo) {
    std::cout << nombre << " ataca a " << objetivo->getNombre() << "!\n";
    objetivo->recibirDanio(10); // Daño básico por ahora
}

void Jugador::recibirDanio(int cantidad) {
    salud -= cantidad;
    if (salud < 0) salud = 0;
    std::cout << nombre << " recibe " << cantidad << " puntos de daño.\n";
}

void Jugador::mostrarEstado() const {
    std::cout << "\n=== ESTADO DE " << nombre << " ===\n";
    std::cout << "Salud: " << salud << "/" << saludMaxima << "\n";
    std::cout << "Energía: " << energia << "\n";
    std::cout << "Nivel: " << nivel << "\n";
}

void Jugador::agregarItem(std::string item) {
    inventario.push_back(item);
    std::cout << "¡Has obtenido: " << item << "!\n";
}

void Jugador::mostrarInventario() const {
    std::cout << "\n=== INVENTARIO ===\n";
    if (inventario.empty()) {
        std::cout << "El inventario está vacío.\n";
    } else {
        for (const auto& item : inventario) {
            std::cout << "- " << item << "\n";
        }
    }
}

int Jugador::getEnergia() const { return energia; }
int Jugador::getNivel() const { return nivel; }