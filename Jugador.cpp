#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre)
    : Entidad(nombre, 100), energia(80), nivel(1), armaEquipada(nullptr), armaduraEquipada(nullptr) {}

Jugador::~Jugador() {
    // Liberar memoria de los items del inventario
    for (auto item : inventario) {
        delete item;
    }
}

void Jugador::atacar(Entidad* objetivo) {
    int danioBase = 10;
    if (armaEquipada) {
        danioBase += armaEquipada->getDanio();
    }
    std::cout << nombre << " ataca a " << objetivo->getNombre() << " causando " << danioBase << " de daño!" << std::endl;
    objetivo->recibirDanio(danioBase);
}

void Jugador::recibirDanio(int cantidad) {
    int danioRecibido = cantidad;
    if (armaduraEquipada) {
        danioRecibido -= armaduraEquipada->getReduccionDanio();
        if (danioRecibido < 0) danioRecibido = 0;
    }
    salud -= danioRecibido;
    if (salud < 0) salud = 0;
    std::cout << nombre << " recibe " << danioRecibido << " puntos de daño." << std::endl;
}

void Jugador::mostrarEstado() const {
    std::cout << "\n=== ESTADO DE " << nombre << " ===" << std::endl;
    std::cout << "Salud: " << salud << "/" << saludMaxima << std::endl;
    std::cout << "Energía: " << energia << std::endl;
    std::cout << "Nivel: " << nivel << std::endl;
    if (armaEquipada) {
        std::cout << "Arma equipada: " << armaEquipada->getNombre() << std::endl;
    }
    if (armaduraEquipada) {
        std::cout << "Armadura equipada: " << armaduraEquipada->getNombre() << std::endl;
    }
}

void Jugador::agregarItem(Item* item) {
    inventario.push_back(item);
    std::cout << "¡Has obtenido: " << item->getNombre() << "!" << std::endl;
}

void Jugador::usarItem(std::string nombreItem) {
    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if ((*it)->getNombre() == nombreItem) {
            (*it)->usar(this);
            // Si es consumible, se consume y elimina del inventario
            if ((*it)->getTipo() == Item::Tipo::CONSUMIBLE) {
                delete *it;
                inventario.erase(it);
            }
            return;
        }
    }
    std::cout << "No tienes el item: " << nombreItem << std::endl;
}

void Jugador::mostrarInventario() const {
    std::cout << "\n=== INVENTARIO ===" << std::endl;
    if (inventario.empty()) {
        std::cout << "El inventario está vacío." << std::endl;
    } else {
        for (const auto& item : inventario) {
            item->mostrarInfo();
        }
    }
}

int Jugador::getEnergia() const { return energia; }
int Jugador::getNivel() const { return nivel; }

void Jugador::equiparArma(Arma* arma) {
    armaEquipada = arma;
    std::cout << "Has equipado el arma: " << arma->getNombre() << std::endl;
}

void Jugador::equiparArmadura(Armadura* armadura) {
    armaduraEquipada = armadura;
    std::cout << "Has equipado la armadura: " << armadura->getNombre() << std::endl;
}