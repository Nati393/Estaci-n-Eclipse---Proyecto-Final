#include "Entidad.h"
#include <iostream>

Entidad::Entidad(std::string nombre, int salud) 
    : nombre(nombre), salud(salud), saludMaxima(salud) {}

bool Entidad::estaVivo() const {
    return salud > 0;
}

void Entidad::mostrarEstado() const {
    std::cout << nombre << " - Salud: " << salud << "/" << saludMaxima;
}

std::string Entidad::getNombre() const { return nombre; }
int Entidad::getSalud() const { return salud; }