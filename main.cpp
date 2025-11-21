#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Jugador.h"
#include "Habitacion.h"
#include "Item.h"
#include "ServidorCorrompido.h"
#include "Parasito.h"
#include "NucleoCorrupto.h"

using namespace std;

// Función para simular combate por turnos
void simularCombate(Jugador& jugador, Enemigo& enemigo) {
    cout << "\n=== COMBATE INICIADO ===" << endl;
    cout << "Te enfrentas a: " << enemigo.getNombre() << endl;

    int turno = 1;
    while (jugador.estaVivo() && enemigo.estaVivo()) {
        cout << "\n--- TURNO " << turno << " ---" << endl;

        // Turno del jugador
        cout << "¿Qué deseas hacer?" << endl;
        cout << "1. ATACAR | 2. USAR OBJETO | 3. HUIR" << endl;

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            jugador.atacar(&enemigo);
            if (!enemigo.estaVivo()) {
                cout << "¡Has derrotado a " << enemigo.getNombre() << "!" << endl;
                jugador.ganarExperiencia(enemigo.getExperienciaOtorgada());
                break;
            }
        } else if (opcion == 2) {
            jugador.mostrarInventario();
            cout << "Escribe el nombre del objeto a usar: ";
            string item;
            cin >> item;
            jugador.usarItem(item);
        } else if (opcion == 3) {
            cout << "Huyes del combate." << endl;
            break;
        } else {
            cout << "Opción no válida. Pierdes tu turno." << endl;
        }

        // Turno del enemigo (si sigue vivo)
        if (enemigo.estaVivo()) {
            enemigo.atacar(&jugador);
            if (!jugador.estaVivo()) {
                cout << "Has sido derrotado..." << endl;
                break;
            }
        }

        turno++;
    }

    if (jugador.estaVivo()) {
        cout << "--- COMBATE TERMINADO ---" << endl;
    }
}

int main() {
    srand(time(0));

    cout << "=== INICIALIZANDO ESTACIÓN ECLIPSE ===" << endl;

    // Crear jugador
    Jugador leia("Leia Jemison");

    // CREAR MAPA COMPLETO
    cout << "\nCREANDO MAPA DE LA ESTACIÓN..." << endl;

    // Habitaciones
    Habitacion camara("Cámara Criogénica",
        "Te despiertas en una cámara criogénica. Las luces de emergencia parpadean sobre filas de cápsulas vacías.");

    Habitacion pasillo("Pasillo Principal",
        "Un largo corredor con ventanas al vacío del espacio. Varios robots de servicio yacen destrozados.");

    Habitacion laboratorio("Laboratorio de Xenobiología",
        "El laboratorio está en caos. Tubos de ensayo rotos y especímenes alienígenas flotan en líquidos.", true);

    Habitacion puente("Puente de Mando",
        "La sala de control principal. Pantallas gigantes muestran advertencias críticas en rojo.", false, true);

    // Configurar conexiones
    camara.agregarSalida(Direccion::NORTE, &pasillo);
    pasillo.agregarSalida(Direccion::SUR, &camara);
    pasillo.agregarSalida(Direccion::ESTE, &laboratorio);
    laboratorio.agregarSalida(Direccion::OESTE, &pasillo);
    laboratorio.agregarSalida(Direccion::NORTE, &puente);
    puente.agregarSalida(Direccion::SUR, &laboratorio);

    // Agregar objetos a las habitaciones
    camara.agregarItem(new Consumible("Kit Médico", 30, 0));
    camara.agregarItem(new Arma("Linterna", 3));

    pasillo.agregarItem(new Consumible("Batería", 0, 25));
    pasillo.agregarItem(new Arma("Pistola Láser", 15));

    laboratorio.agregarItem(new Armadura("Traje Reforzado", 5, false));
    laboratorio.agregarItem(new Consumible("Antídoto", 20, 10));

    puente.agregarItem(new Armadura("Traje Antirradiación", 3, true));

    // Enemigos
    pasillo.agregarEnemigo(new ServidorCorrompido());
    laboratorio.agregarEnemigo(new Parasito());
    puente.agregarEnemigo(new NucleoCorrupto());

    // SIMULACIÓN DEL JUEGO
    Habitacion* ubicacionActual = &camara;

    cout << "\nINICIANDO SIMULACIÓN DE JUEGO..." << endl;

    // Cámara Criogénica
    cout << "\nUbicación actual: Cámara Criogénica" << endl;
    leia.explorarHabitacion(ubicacionActual);

    // Recoger objetos iniciales
    leia.agregarItem(new Consumible("Kit Médico", 30, 0));
    leia.agregarItem(new Arma("Linterna", 3));

    // Moverse al Pasillo
    cout << "\nMoviéndose al Pasillo Principal..." << endl;
    ubicacionActual = ubicacionActual->getSalida(Direccion::NORTE);
    leia.explorarHabitacion(ubicacionActual);

    // Combate con Servidor Corrompido
    if (ubicacionActual->tieneEnemigos()) {
        auto& enemigos = ubicacionActual->getEnemigos();
        simularCombate(leia, *enemigos[0]);
    }

    // Recoger los objetos del pasillo
    leia.agregarItem(new Consumible("Batería", 0, 25));
    leia.agregarItem(new Arma("Pistola Láser", 15));
    leia.equiparArma(dynamic_cast<Arma*>(leia.tieneItem("Pistola Láser") ? new Arma("Pistola Láser", 15) : nullptr));

    // Moverse al Laboratorio
    cout << "\nMoviéndose al Laboratorio de Xenobiología..." << endl;
    ubicacionActual = ubicacionActual->getSalida(Direccion::ESTE);
    leia.explorarHabitacion(ubicacionActual);

    // Combate con Parásito
    if (ubicacionActual->tieneEnemigos()) {
        auto& enemigos = ubicacionActual->getEnemigos();
        simularCombate(leia, *enemigos[0]);
    }

    // Equipar armadura del laboratorio
    leia.agregarItem(new Armadura("Traje Reforzado", 5, false));
    leia.equiparArmadura(dynamic_cast<Armadura*>(leia.tieneItem("Traje Reforzado") ? new Armadura("Traje Reforzado", 5, false) : nullptr));

    // Moverse al Puente de Mando
    cout << "\nMoviéndose al Puente de Mando..." << endl;
    ubicacionActual = ubicacionActual->getSalida(Direccion::NORTE);
    leia.explorarHabitacion(ubicacionActual);

    // Combate con el Jefe Final
    if (ubicacionActual->tieneEnemigos()) {
        auto& enemigos = ubicacionActual->getEnemigos();
        cout << "\nENFRENTAMIENTO FINAL CON EL JEFE" << endl;
        simularCombate(leia, *enemigos[0]);
    }

    // Final del juego
    if (leia.estaVivo()) {
        cout << "\n¡FELICIDADES! HAS COMPLETADO LA MISIÓN" << endl;
        cout << "Has restaurado el control de la Estación Eclipse." << endl;
    } else {
        cout << "\nGAME OVER - La estación queda en silencio eterno..." << endl;
    }

    leia.mostrarEstado();
    cout << "\n=== MAPA COMPLETO Y SISTEMA DE COMBATE IMPLEMENTADO ===" << endl;

    return 0;
}