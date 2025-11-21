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
    void mostrarInfo() const override;

    // Getters añadidos
    int getValorCuracion() const;
    int getValorEnergia() const;
};

class Arma : public Item {
private:
    int danio;

public:
    Arma(std::string nombre, int danio);
    void usar(Jugador* jugador) override;
    void mostrarInfo() const override;
    int getDanio() const;
};

class Armadura : public Item {
private:
    int reduccionDanio;
    bool proteccionRadiacion;

public:
    Armadura(std::string nombre, int reduccion, bool proteccionRad);
    void usar(Jugador* jugador) override;
    void mostrarInfo() const override;
    int getReduccionDanio() const;
    bool tieneProteccionRadiacion() const;
};

// Clase Llave
class Llave : public Item {
public:
    Llave(std::string nombre) : Item(nombre, Tipo::LLAVE) {}

    void usar(Jugador* jugador) override {
        std::cout << "Usas la llave: " << nombre << std::endl;
    }

    void mostrarInfo() const override {
        std::cout << "Item: " << nombre << " [Llave]" << std::endl;
    }
};

#endif