#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

// Forward declaration
class Jugador;

class Item {
public:
    enum class Tipo {
        CONSUMIBLE,
        ARMA, 
        ARMADURA,
        LLAVE
    };

    Item(std::string nombre, Tipo tipo);
    virtual ~Item() = default;
    
    virtual void usar(Jugador* jugador) = 0;
    virtual void mostrarInfo() const;
    
    std::string getNombre() const;
    Tipo getTipo() const;

protected:
    std::string nombre;
    Tipo tipo;
};

class Consumible : public Item {
private:
    int valorCuracion;
    int valorEnergia;

public:
    Consumible(std::string nombre, int curacion, int energia);
    void usar(Jugador* jugador) override;
    void mostrarInfo() const;
};

class Arma : public Item {
private:
    int danio;

public:
    Arma(std::string nombre, int danio);
    void usar(Jugador* jugador) override;
    void mostrarInfo() const;
    int getDanio() const;
};

class Armadura : public Item {
private:
    int reduccionDanio;
    bool proteccionRadiacion;

public:
    Armadura(std::string nombre, int reduccion, bool proteccionRad);
    void usar(Jugador* jugador) override;
    void mostrarInfo() const;
    int getReduccionDanio() const;
    bool tieneProteccionRadiacion() const;
};

#endif