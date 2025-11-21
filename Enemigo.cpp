#include "Enemigo.h"
#include "Jugador.h"
#include <iostream>

Enemigo::Enemigo(std::string nombre, int salud, int danio, int experiencia)
    : Entidad(nombre, salud), danioBase(danio), experienciaOtorgada(experiencia) {}

void Enemigo::atacar(Entidad* objetivo) {
    std::cout << nombre << " ataca a " << objetivo->getNombre() << "!" << std::endl;
    objetivo->recibirDanio(danioBase);
}

void Enemigo::recibirDanio(int cantidad) {
    salud -= cantidad;
    if (salud < 0) salud = 0;
    std::cout << nombre << " recibe " << cantidad << " puntos de daño." << std::endl;
}

int Enemigo::getExperienciaOtorgada() const {
    return experienciaOtorgada;
}