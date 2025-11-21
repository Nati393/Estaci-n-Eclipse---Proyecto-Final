#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre)
    : Entidad(nombre, 100), energia(80), energiaMaxima(80), nivel(1),
      experiencia(0), experienciaSiguienteNivel(100), radiacionAcumulada(0),
      armaEquipada(nullptr), armaduraEquipada(nullptr) {}

Jugador::~Jugador() {
    for (auto item : inventario) {
        delete item;
    }
}

void Jugador::atacar(Entidad* objetivo) {
    int danioBase = 10 + (nivel * 2);
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
    std::cout << "Energía: " << energia << "/" << energiaMaxima << std::endl;
    std::cout << "Nivel: " << nivel << " (XP: " << experiencia << "/" << experienciaSiguienteNivel << ")" << std::endl;
    if (armaEquipada) {
        std::cout << "Arma equipada: " << armaEquipada->getNombre() << std::endl;
    }
    if (armaduraEquipada) {
        std::cout << "Armadura equipada: " << armaduraEquipada->getNombre() << std::endl;
    }
    if (radiacionAcumulada > 0) {
        std::cout << "⚠️  Radiación acumulada: " << radiacionAcumulada << std::endl;
    }
}

void Jugador::agregarItem(Item* item) {
    inventario.push_back(item);
}

void Jugador::usarItem(std::string nombreItem) {
    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if ((*it)->getNombre() == nombreItem) {
            (*it)->usar(this);

            // Si es un arma, equiparla
            if ((*it)->getTipo() == Item::Tipo::ARMA) {
                equiparArma(dynamic_cast<Arma*>(*it));
            }
            // Si es armadura, equiparla
            else if ((*it)->getTipo() == Item::Tipo::ARMADURA) {
                equiparArmadura(dynamic_cast<Armadura*>(*it));
            }
            // Si es consumible, eliminarlo después de usar
            else if ((*it)->getTipo() == Item::Tipo::CONSUMIBLE) {
                // Aplicar efectos del consumible
                Consumible* consumible = dynamic_cast<Consumible*>(*it);
                salud += consumible->getValorCuracion();
                if (salud > saludMaxima) salud = saludMaxima;
                energia += consumible->getValorEnergia();
                if (energia > energiaMaxima) energia = energiaMaxima;

                std::cout << "¡Salud recuperada! Ahora tienes " << salud << "/" << saludMaxima << std::endl;
                std::cout << "¡Energía recuperada! Ahora tienes " << energia << "/" << energiaMaxima << std::endl;

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

void Jugador::reducirEnergia(int cantidad) {
    energia -= cantidad;
    if (energia < 0) energia = 0;
    std::cout << "Energía reducida en " << cantidad << ". Energía actual: " << energia << std::endl;
}

void Jugador::ganarExperiencia(int cantidad) {
    experiencia += cantidad;
    std::cout << "¡Ganas " << cantidad << " puntos de experiencia!" << std::endl;
    if (experiencia >= experienciaSiguienteNivel) {
        subirNivel();
    }
}

void Jugador::subirNivel() {
    nivel++;
    experiencia = 0;
    experienciaSiguienteNivel = nivel * 100;

    saludMaxima += 20;
    salud = saludMaxima;
    energiaMaxima += 10;
    energia = energiaMaxima;

    std::cout << "\n ¡FELICIDADES! HAS SUBIDO AL NIVEL " << nivel << "!" << std::endl;
    std::cout << "Salud máxima aumentada a " << saludMaxima << std::endl;
    std::cout << "Energía máxima aumentada a " << energiaMaxima << std::endl;
}

bool Jugador::tieneItem(std::string nombreItem) const {
    for (const auto& item : inventario) {
        if (item->getNombre() == nombreItem) {
            return true;
        }
    }
    return false;
}

void Jugador::equiparArma(Arma* arma) {
    armaEquipada = arma;
    std::cout << "Has equipado el arma: " << arma->getNombre() << std::endl;
}

void Jugador::equiparArmadura(Armadura* armadura) {
    armaduraEquipada = armadura;
    std::cout << "Has equipado la armadura: " << armadura->getNombre() << std::endl;
}

// Getters
int Jugador::getEnergia() const { return energia; }
int Jugador::getEnergiaMaxima() const { return energiaMaxima; }
int Jugador::getNivel() const { return nivel; }
int Jugador::getExperiencia() const { return experiencia; }
int Jugador::getExperienciaSiguienteNivel() const { return experienciaSiguienteNivel; }