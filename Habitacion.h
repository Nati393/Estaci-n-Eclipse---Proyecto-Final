#ifndef HABITACION_H
#define HABITACION_H

#include "Direccion.h"
#include "Enemigo.h"
#include "Item.h"
#include <string>
#include <map>
#include <vector>

class Habitacion {
private:
    std::string nombre;
    std::string descripcion;
    std::vector<Enemigo*> enemigos;
    std::vector<Item*> objetos;
    std::map<Direccion, Habitacion*> salidas;
    bool tieneRadiacion;
    bool requiereLlave;

public:
    Habitacion(std::string nombre, std::string descripcion, bool radiacion = false, bool llave = false);
    ~Habitacion();

    void agregarSalida(Direccion direccion, Habitacion* habitacion);
    void agregarEnemigo(Enemigo* enemigo);
    void agregarItem(Item* item);
    void mostrarDescripcion() const;
    void mostrarSalidas() const;
    void mostrarEnemigos() const;
    void mostrarObjetos() const;
    Habitacion* getSalida(Direccion direccion) const;
    bool tieneEnemigos() const;
    bool getRequiereLlave() const;
    bool getTieneRadiacion() const;

    // Para el sistema de combate
    std::vector<Enemigo*>& getEnemigos();
    void eliminarEnemigo(Enemigo* enemigo);
};

#endif