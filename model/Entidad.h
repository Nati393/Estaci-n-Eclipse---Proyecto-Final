#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <string>

class Entidad {
protected:
    std::string nombre;
    int salud;
    int saludMaxima;

public:
    Entidad(std::string nombre, int salud);
    virtual ~Entidad() = default;
    
    // Métodos virtuales
    virtual void atacar(Entidad* objetivo) = 0;
    virtual void recibirDanio(int cantidad) = 0;
    
    // Métodos concretos
    bool estaVivo() const;
    void mostrarEstado() const;
    
    // Getters
    std::string getNombre() const;
    int getSalud() const;
};

#endif