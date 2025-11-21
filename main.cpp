#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Jugador.h"
#include "Habitacion.h"
#include "Item.h"
#include "ServidorCorrompido.h"
#include "Parasito.h"

using namespace std;

int main() {
    srand(time(0)); // Inicializar semilla para números aleatorios

    cout << "=== INICIALIZANDO SISTEMA ===" << endl;

    // Crear jugador
    Jugador leia("Leia Jemison");
    leia.mostrarEstado();

    // Crear habitaciones básicas
    Habitacion camara("Camara Criogenica",
        "Te despiertas en una camara criogenica. Luces de emergencia parpadean.");

    Habitacion pasillo("Pasillo Principal",
        "Un largo corredor con ventanas al vacio del espacio.");

    // Conectar habitaciones
    camara.agregarSalida(Direccion::NORTE, &pasillo);
    pasillo.agregarSalida(Direccion::SUR, &camara);

    // Demo de movimiento
    Habitacion* ubicacionActual = &camara;
    ubicacionActual->mostrarDescripcion();
    ubicacionActual->mostrarSalidas();

    // Demo de sistema de items
    leia.agregarItem(new Consumible("Kit Medico", 30, 0));
    leia.agregarItem(new Consumible("Bateria", 0, 25));
    leia.agregarItem(new Arma("Pistola Laser", 15));
    leia.agregarItem(new Armadura("Traje Reforzado", 5, false));

    leia.mostrarInventario();

    // Probar uso de items
    leia.usarItem("Kit Medico");
    leia.mostrarInventario();

    // DEMO DE SISTEMA DE ENEMIGOS
    cout << "\n=== DEMOSTRACION SISTEMA DE ENEMIGOS ===" << endl;

    // Crear enemigos
    ServidorCorrompido servidor;
    Parasito parasito;

    cout << "\n--- ENEMIGOS CREADOS ---" << endl;
    servidor.mostrarEstado();
    parasito.mostrarEstado();

    cout << "\n--- SIMULACION DE COMBATE ---" << endl;

    // Turno 1: Enemigos atacan
    servidor.atacar(&leia);
    parasito.atacar(&leia);

    // Turno 2: Jugador contraataca
    leia.atacar(&servidor);
    leia.atacar(&parasito);

    cout << "\n--- ESTADO DESPUES DEL COMBATE ---" << endl;
    leia.mostrarEstado();
    servidor.mostrarEstado();
    parasito.mostrarEstado();

    // Demo de experiencia
    leia.ganarExperiencia(servidor.getExperienciaOtorgada());
    leia.ganarExperiencia(parasito.getExperienciaOtorgada());

    cout << "\n=== SISTEMA DE ENEMIGOS IMPLEMENTADO ===" << endl;

    return 0;
}