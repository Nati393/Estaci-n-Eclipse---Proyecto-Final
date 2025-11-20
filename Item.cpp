#include "Item.h"
#include "Jugador.h"

// Implementación de Item base
Item::Item(std::string nombre, Tipo tipo) : nombre(nombre), tipo(tipo) {}

void Item::mostrarInfo() const {
    std::cout << "Item: " << nombre;
}

std::string Item::getNombre() const { return nombre; }
Item::Tipo Item::getTipo() const { return tipo; }

// Implementación de Consumible
Consumible::Consumible(std::string nombre, int curacion, int energia)
    : Item(nombre, Tipo::CONSUMIBLE), valorCuracion(curacion), valorEnergia(energia) {}

void Consumible::usar(Jugador* jugador) {
    std::cout << "Usando " << nombre << " - Cura " << valorCuracion << " de salud y " << valorEnergia << " de energia." << std::endl;
}

void Consumible::mostrarInfo() const {
    Item::mostrarInfo();
    std::cout << " [Consumible] - Cura: " << valorCuracion << ", Energia: " << valorEnergia << std::endl;
}

// Implementación de Arma
Arma::Arma(std::string nombre, int danio)
    : Item(nombre, Tipo::ARMA), danio(danio) {}

void Arma::usar(Jugador* jugador) {
    std::cout << "Equipando arma: " << nombre << " (Daño: " << danio << ")" << std::endl;
}

void Arma::mostrarInfo() const {
    Item::mostrarInfo();
    std::cout << " [Arma] - Daño: " << danio << std::endl;
}

int Arma::getDanio() const { return danio; }

// Implementación de Armadura
Armadura::Armadura(std::string nombre, int reduccion, bool proteccionRad)
    : Item(nombre, Tipo::ARMADURA), reduccionDanio(reduccion), proteccionRadiacion(proteccionRad) {}

void Armadura::usar(Jugador* jugador) {
    std::cout << "Equipando armadura: " << nombre << " (Reducción: " << reduccionDanio << ")" << std::endl;
}

void Armadura::mostrarInfo() const {
    Item::mostrarInfo();
    std::cout << " [Armadura] - Reducción: " << reduccionDanio;
    if (proteccionRadiacion) std::cout << " - Protege de radiación";
    std::cout << std::endl;
}

int Armadura::getReduccionDanio() const { return reduccionDanio; }
bool Armadura::tieneProteccionRadiacion() const { return proteccionRadiacion; }