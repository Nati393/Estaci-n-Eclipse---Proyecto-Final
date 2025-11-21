#include "Parasito.h"
#include "Enemigo.h"
#include "Jugador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Parasito::Parasito()
    : Enemigo("Parasito Bioluminiscente", 40, 15, 75),
      probabilidadVeneno(30), danioVeneno(5), duracionVeneno(3) {}

void Parasito::atacar(Entidad* objetivo) {
    Enemigo::atacar(objetivo);  // Corregí el typo "objectivo"

    // 30% de probabilidad de envenenar
    if (rand() % 100 < probabilidadVeneno) {
        std::cout << "¡El Parásito intenta envenenarte!" << std::endl;
        habilidadEspecial(dynamic_cast<Jugador*>(objetivo));  // Corregí el cast
    }
}

void Parasito::habilidadEspecial(Jugador* jugador) {
    std::cout << "¡ENVENENADO! Recibirás " << danioVeneno << " de daño por " << duracionVeneno << " turnos." << std::endl;
}