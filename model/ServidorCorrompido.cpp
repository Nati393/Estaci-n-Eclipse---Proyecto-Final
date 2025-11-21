#include "ServidorCorrompido.h"
#include "Enemigo.h"
#include "Jugador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

ServidorCorrompido::ServidorCorrompido()
    : Enemigo("Servidor Corrompido", 30, 10, 50),
      probabilidadSobrecarga(20), danioSobrecarga(5) {}

void ServidorCorrompido::atacar(Entidad* objetivo) {
    Enemigo::atacar(objetivo);

    // 20% de probabilidad de sobrecarga
    if (rand() % 100 < probabilidadSobrecarga) {
        std::cout << "¡El Servidor Corrompido intenta sobrecargar tus sistemas!" << std::endl;
        habilidadEspecial(dynamic_cast<Jugador*>(objetivo));
    }
}

void ServidorCorrompido::habilidadEspecial(Jugador* jugador) {
    std::cout << "¡SOBRECARGA! Pierdes " << danioSobrecarga << " puntos de energía." << std::endl;
    jugador->reducirEnergia(danioSobrecarga);
}