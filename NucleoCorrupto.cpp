#include "NucleoCorrupto.h"
#include "Jugador.h"
#include <iostream>
#include <cstdlib>

NucleoCorrupto::NucleoCorrupto()
    : Enemigo("Núcleo Corrupto", 100, 20, 200), 
      turnosParaInvocar(3), contadorTurnos(0), refuerzosInvocados(false) {}

void NucleoCorrupto::atacar(Entidad* objetivo) {
    Enemigo::atacar(objetivo);
    
    contadorTurnos++;
    if (contadorTurnos >= turnosParaInvocar && !refuerzosInvocados) {
        std::cout << "¡El Núcleo Corrupto empieza a emitir pulsos de energía!" << std::endl;
        habilidadEspecial(dynamic_cast<Jugador*>(objetivo));
        contadorTurnos = 0;
    }
}

void NucleoCorrupto::habilidadEspecial(Jugador* jugador) {
    // El 50% de probabilidad de poder invocar refuerzos o corromper los sistemas
    if (rand() % 100 < 50) {
        invocarRefuerzos();
    } else {
        corromperSistemas(jugador);
    }
}

void NucleoCorrupto::invocarRefuerzos() {
    std::cout << "¡NÚCLEO CORRUPTO INVOCA REFUERZOS!" << std::endl;
    std::cout << "Un Servidor Corrompido adicional aparece en la sala." << std::endl;
    refuerzosInvocados = true;
}

void NucleoCorrupto::corromperSistemas(Jugador* jugador) {
    std::cout << "¡CORRUPCIÓN DE SISTEMAS!" << std::endl;
    std::cout << "El Núcleo Corrupto drena 10 puntos de energía de tus sistemas." << std::endl;
    jugador->reducirEnergia(10);
}