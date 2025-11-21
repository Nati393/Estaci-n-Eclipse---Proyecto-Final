#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include "Item.h"
#include <vector>

class Jugador : public Entidad {
private:
    int energia;
    int energiaMaxima;
    int nivel;
    int experiencia;
    int experienciaSiguienteNivel;
    int radiacionAcumulada;
    std::vector<Item*> inventario;
    Arma* armaEquipada;
    Armadura* armaduraEquipada;

public:
    Jugador(std::string nombre);
    ~Jugador();

    void atacar(Entidad* objetivo) override;
    void recibirDanio(int cantidad) override;
    void mostrarEstado() const;
    void agregarItem(Item* item);
    void usarItem(std::string nombreItem);
    void mostrarInventario() const;
    void reducirEnergia(int cantidad);
    void ganarExperiencia(int cantidad);
    void subirNivel();
    bool tieneItem(std::string nombreItem) const;
    bool tieneItems() const { return !inventario.empty(); }
    void equiparArma(Arma* arma);
    void equiparArmadura(Armadura* armadura);

    // Getters
    int getEnergia() const;
    int getEnergiaMaxima() const;
    int getNivel() const;
    int getExperiencia() const;
    int getExperienciaSiguienteNivel() const;
};

#endif