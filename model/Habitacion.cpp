#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion(std::string nombre, std::string descripcion, bool radiacion, bool llave)
    : nombre(nombre), descripcion(descripcion), tieneRadiacion(radiacion), requiereLlave(llave) {}

Habitacion::~Habitacion() {
    for (auto enemigo : enemigos) {
        delete enemigo;
    }
    for (auto objeto : objetos) {
        delete objeto;
    }
}

void Habitacion::agregarSalida(Direccion direccion, Habitacion* habitacion) {
    salidas[direccion] = habitacion;
}

void Habitacion::agregarEnemigo(Enemigo* enemigo) {
    enemigos.push_back(enemigo);
}

void Habitacion::agregarItem(Item* item) {
    objetos.push_back(item);
}

void Habitacion::mostrarDescripcion() const {
    std::cout << "\n=== " << nombre << " ===" << std::endl;
    std::cout << descripcion << std::endl;
    if (tieneRadiacion) {
        std::cout << "ZONA CONTAMINADA: Niveles de radiación elevados detectados" << std::endl;
    }
    if (requiereLlave) {
        std::cout << "Esta habitación requiere una llave especial para acceder" << std::endl;
    }
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
    std::cout << std::endl;
}

void Habitacion::mostrarEnemigos() const {
    if (!enemigos.empty()) {
        std::cout << "Enemigos en la habitación:" << std::endl;
        for (const auto& enemigo : enemigos) {
            enemigo->mostrarEstado();
            std::cout << std::endl;
        }
    }
}

void Habitacion::mostrarObjetos() const {
    if (!objetos.empty()) {
        std::cout << "Objetos en la habitación:" << std::endl;
        for (const auto& objeto : objetos) {
            objeto->mostrarInfo();
        }
    }
}

Habitacion* Habitacion::getSalida(Direccion direccion) const {
    auto it = salidas.find(direccion);
    if (it != salidas.end()) {
        return it->second;
    }
    return nullptr;
}

std::string Habitacion::getNombre() const {
    return nombre;
}

bool Habitacion::tieneEnemigos() const {
    return !enemigos.empty();
}

bool Habitacion::getRequiereLlave() const {
    return requiereLlave;
}

bool Habitacion::getTieneRadiacion() const {
    return tieneRadiacion;
}

std::vector<Enemigo*>& Habitacion::getEnemigos() {
    return enemigos;
}

void Habitacion::eliminarEnemigo(Enemigo* enemigo) {
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it) {
        if (*it == enemigo) {
            delete *it;
            enemigos.erase(it);
            break;
        }
    }
}