#ifndef SERVIDOR_CORROMPIDO_H
#define SERVIDOR_CORROMPIDO_H

#include "Enemigo.h"

class ServidorCorrompido : public Enemigo {
private:
    int probabilidadSobrecarga;
    int danioSobrecarga;

public:
    ServidorCorrompido();
    void atacar(Entidad* objetivo) override;
    void habilidadEspecial(Jugador* jugador) override;
};

#endif