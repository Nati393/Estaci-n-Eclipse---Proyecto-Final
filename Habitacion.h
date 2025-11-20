#ifndef HABITACION_H
#define HABITACION_H

#include "Direccion.h"
#include <string>
#include <map>

class Habitacion {
private:
    std::string nombre;
    std::string descripcion;
    std::map<Direccion, Habitacion*> salidas;

public:
    Habitacion(std::string nombre, std::string descripcion);
    
    void agregarSalida(Direccion direccion, Habitacion* habitacion);
    void mostrarDescripcion() const;
    void mostrarSalidas() const;
    Habitacion* getSalida(Direccion direccion) const;
    
    std::string getNombre() const;
};

#endif