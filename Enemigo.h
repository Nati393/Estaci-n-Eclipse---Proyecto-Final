#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"


class Jugador;

class Enemigo : public Entidad {
protected:
    int danioBase;
    int experienciaOtorgada;

public:
    Enemigo(std::string nombre, int salud, int danio, int experiencia);
    virtual ~Enemigo() = default;

    virtual void atacar(Entidad* objetivo) override;
    virtual void recibirDanio(int cantidad) override;
    virtual void habilidadEspecial(Jugador* jugador) = 0;

    int getExperienciaOtorgada() const;
};

#endif