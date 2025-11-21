#ifndef NUCLEO_CORRUPTO_H
#define NUCLEO_CORRUPTO_H

#include "Enemigo.h"

class NucleoCorrupto : public Enemigo {
private:
    int turnosParaInvocar;
    int contadorTurnos;
    bool refuerzosInvocados;

public:
    NucleoCorrupto();
    void atacar(Entidad* objetivo) override;
    void habilidadEspecial(Jugador* jugador) override;
    void invocarRefuerzos();
    void corromperSistemas(Jugador* jugador);
};

#endif