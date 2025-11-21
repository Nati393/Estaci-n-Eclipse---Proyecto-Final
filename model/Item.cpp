#include "Item.h"
#include "Jugador.h"
#include <iostream>

// Implementación de Item base
Item::Item(std::string nombre, Tipo tipo) : nombre(nombre), tipo(tipo) {}

void Item::mostrarInfo() const {
    std::cout << "Item: " << nombre << " [Tipo: " << static_cast<int>(tipo) << "]" << std::endl;
}

std::string Item::getNombre() const { return nombre; }
Item::Tipo Item::getTipo() const { return tipo; }

// Implementación de Consumible
Consumible::Consumible(std::string nombre, int curacion, int energia)
    : Item(nombre, Tipo::CONSUMIBLE), valorCuracion(curacion), valorEnergia(energia) {}

void Consumible::usar(Jugador* jugador) {
    // La implementación real está en Jugador::usarItem
}

void Consumible::mostrarInfo() const {
    std::cout << "Item: " << nombre << " [Consumible] - Cura: " << valorCuracion << ", Energía: " << valorEnergia << std::endl;
}

// GETTERS IMPLEMENTADOS
int Consumible::getValorCuracion() const { return valorCuracion; }
int Consumible::getValorEnergia() const { return valorEnergia; }

// Implementación de Arma
Arma::Arma(std::string nombre, int danio)
    : Item(nombre, Tipo::ARMA), danio(danio) {}

void Arma::usar(Jugador* jugador) {
    // La implementación real está en Jugador::usarItem
}

void Arma::mostrarInfo() const {
    std::cout << "Item: " << nombre << " [Arma] - Daño: " << danio << std::endl;
}

int Arma::getDanio() const { return danio; }

// Implementación de Armadura
Armadura::Armadura(std::string nombre, int reduccion, bool proteccionRad)
    : Item(nombre, Tipo::ARMADURA), reduccionDanio(reduccion), proteccionRadiacion(proteccionRad) {}

void Armadura::usar(Jugador* jugador) {
    // La implementación real está en Jugador::usarItem
}

void Armadura::mostrarInfo() const {
    std::cout << "Item: " << nombre << " [Armadura] - Reducción: " << reduccionDanio << ", Protección radiación: " << proteccionRadiacion << std::endl;
}

int Armadura::getReduccionDanio() const { return reduccionDanio; }
bool Armadura::tieneProteccionRadiacion() const { return proteccionRadiacion; }