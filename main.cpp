#include <iostream>
#include "Jugador.h"
#include "Habitacion.h"

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

    // Inventario
    leia.agregarItem("Kit Médico");
    leia.agregarItem("Linterna");
    leia.mostrarInventario();

    cout << "\n=== SISTEMA INICIALIZADO CORRECTAMENTE ===" << endl;

    return 0;
}