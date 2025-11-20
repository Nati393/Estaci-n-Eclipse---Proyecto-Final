#include <iostream>
#include "Jugador.h"
#include "Habitacion.h"
#include "Item.h"

using namespace std;

int main() {
    cout << "=== INICIALIZANDO SISTEMA ===" << endl;

    // Crear jugador
    Jugador leia("Leia Jemison");
    leia.mostrarEstado();

    // Crear habitaciones
    Habitacion camara("Cámara Criogénica",
        "Te despiertas en una cámara criogénica. Luces de emergencia parpadean.");

    Habitacion pasillo("Pasillo Principal",
        "Un largo corredor con ventanas al vacío del espacio.");

    // Conectar habitaciones
    camara.agregarSalida(Direccion::NORTE, &pasillo);
    pasillo.agregarSalida(Direccion::SUR, &camara);

    //Movimiento
    Habitacion* ubicacionActual = &camara;
    ubicacionActual->mostrarDescripcion();
    ubicacionActual->mostrarSalidas();

    //Sistema de items
    leia.agregarItem(new Consumible("Kit Medico", 30, 0));
    leia.agregarItem(new Consumible("Bateria", 0, 25));
    leia.agregarItem(new Arma("Pistola Laser", 15));
    leia.agregarItem(new Armadura("Traje Reforzado", 5, false));

    leia.mostrarInventario();

   // Probar uso de items
    leia.usarItem("Kit Medico");
    leia.mostrarInventario();

    cout << "\n=== SISTEMA INICIALIZADO CORRECTAMENTE ===" << endl;

    return 0;
}