#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include <vector>
#include <string>

class Jugador : public Entidad {
private:
    int energia;
    int nivel;
    std::vector<std::string> inventario;

public:
    Jugador(std::string nombre);
    
    // Implementación de métodos abstractos
    void atacar(Entidad* objetivo) override;
    void recibirDanio(int cantidad) override;
    
    // Métodos específicos del jugador
    void mostrarEstado() const;
    void agregarItem(std::string item);
    void mostrarInventario() const;
    
    // Getters
    int getEnergia() const;
    int getNivel() const;
};

#endif