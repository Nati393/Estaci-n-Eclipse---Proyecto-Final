#ifndef PARASITO_H
#define PARASITO_H

#include "Enemigo.h"

class Parasito : public Enemigo {
private:
    int probabilidadVeneno;
    int danioVeneno;
    int duracionVeneno;

public:
    Parasito();
    void atacar(Entidad* objetivo) override;
    void habilidadEspecial(Jugador* jugador) override;
};

#endif