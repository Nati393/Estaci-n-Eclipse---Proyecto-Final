#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion(std::string nombre, std::string descripcion) 
    : nombre(nombre), descripcion(descripcion) {}

void Habitacion::agregarSalida(Direccion direccion, Habitacion* habitacion) {
    salidas[direccion] = habitacion;
}

void Habitacion::mostrarDescripcion() const {
    std::cout << "\n=== " << nombre << " ===\n";
    std::cout << descripcion << "\n";
}

void Habitacion::mostrarSalidas() const {
    std::cout << "Salidas disponibles: ";
    for (const auto& salida : salidas) {
        switch (salida.first) {
            case Direccion::NORTE: std::cout << "NORTE "; break;
            case Direccion::SUR: std::cout << "SUR "; break;
            case Direccion::ESTE: std::cout << "ESTE "; break;
            case Direccion::OESTE: std::cout << "OESTE "; break;
        }
    }
    std::cout << "\n";
}

Habitacion* Habitacion::getSalida(Direccion direccion) const {
    auto it = salidas.find(direccion);
    if (it != salidas.end()) {
        return it->second;
    }
    return nullptr;
}

std::string Habitacion::getNombre() const { return nombre; }