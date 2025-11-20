#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include "Item.h"
#include <vector>
#include <string>

class Jugador : public Entidad {
private:
    int energia;
    int nivel;
    std::vector<Item*> inventario;
    Arma* armaEquipada;
    Armadura* armaduraEquipada;

public:
    Jugador(std::string nombre);
    ~Jugador(); // Necesitamos destructor para limpiar items

    // Implementación de métodos abstractos
    void atacar(Entidad* objetivo) override;
    void recibirDanio(int cantidad) override;

    // Métodos específicos del jugador
    void mostrarEstado() const;
    void agregarItem(Item* item);
    void usarItem(std::string nombreItem);
    void mostrarInventario() const;

    // Getters
    int getEnergia() const;
    int getNivel() const;

    // Métodos para equipar
    void equiparArma(Arma* arma);
    void equiparArmadura(Armadura* armadura);
};

#endif