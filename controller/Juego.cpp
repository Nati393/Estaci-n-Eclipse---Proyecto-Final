#include "Juego.h"
#include "model/ServidorCorrompido.h"
#include "model/Parasito.h"
#include "model/NucleoCorrupto.h"
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Juego::Juego() : jugador(nullptr), habitacionActual(nullptr), juegoActivo(false) {
    srand(time(0)); // Para números aleatorios en combate
}

Juego::~Juego() {
    delete jugador;
    for (auto habitacion : habitaciones) {
        delete habitacion;
    }
}

void Juego::inicializarJuego() {
    InterfazConsola::limpiarPantalla();
    InterfazConsola::mostrarTitulo(Mensajes::BIENVENIDA);
    InterfazConsola::mostrarMensaje(Mensajes::DESCRIPCION_JUEGO);

    // Crear jugador
    jugador = new Jugador("Leia Jemison");

    // Crear mapa
    crearMapa();

    juegoActivo = true;
}

void Juego::crearMapa() {
    // Crear habitaciones
    Habitacion* camara = new Habitacion("Cámara Criogénica",
        "Te despiertas en una cámara criogénica. Luces de emergencia parpadean sobre filas de cápsulas vacías.");

    Habitacion* pasillo = new Habitacion("Pasillo Principal",
        "Un largo corredor con ventanas al vacío del espacio. Varios robots de servicio yacen destrozados.");

    Habitacion* laboratorio = new Habitacion("Laboratorio de Xenobiología",
        "El laboratorio está en caos. Tubos de ensayo rotos y especímenes alienígenas flotan en líquidos.", true);

    Habitacion* puente = new Habitacion("Puente de Mando",
        "La sala de control principal. Pantallas gigantes muestran advertencias críticas en rojo sangre.", false, true);

    // Configurar conexiones
    camara->agregarSalida(Direccion::NORTE, pasillo);
    pasillo->agregarSalida(Direccion::SUR, camara);
    pasillo->agregarSalida(Direccion::ESTE, laboratorio);
    laboratorio->agregarSalida(Direccion::OESTE, pasillo);
    laboratorio->agregarSalida(Direccion::NORTE, puente);
    puente->agregarSalida(Direccion::SUR, laboratorio);

    // Agregar objetos
    camara->agregarItem(new Consumible("Kit_Médico", 30, 0));
    camara->agregarItem(new Arma("Linterna", 3));

    pasillo->agregarItem(new Consumible("Batería", 0, 25));
    pasillo->agregarItem(new Arma("Pistola_Láser", 15));
    pasillo->agregarItem(new Llave("Llave_Nivel_1")); // AÑADIR LLAVE

    laboratorio->agregarItem(new Armadura("Traje_Reforzado", 5, false));

    puente->agregarItem(new Armadura("Traje_Antirradiación", 3, true));

    // Agregar enemigos
    pasillo->agregarEnemigo(new ServidorCorrompido());
    laboratorio->agregarEnemigo(new Parasito());
    puente->agregarEnemigo(new NucleoCorrupto());

    // Guardar referencia a las habitaciones
    habitaciones.push_back(camara);
    habitaciones.push_back(pasillo);
    habitaciones.push_back(laboratorio);
    habitaciones.push_back(puente);

    habitacionActual = camara;
}

void Juego::ejecutar() {
    while (juegoActivo && jugador->estaVivo()) {
        // Mostrar estado actual
        habitacionActual->mostrarDescripcion();
        habitacionActual->mostrarSalidas();
        habitacionActual->mostrarEnemigos();
        habitacionActual->mostrarObjetos();

        // Si hay enemigos, iniciar combate automáticamente
        if (habitacionActual->tieneEnemigos()) {
            iniciarCombate();
            // Si el jugador murió en combate, salir
            if (!jugador->estaVivo()) {
                break;
            }
            // Si ganó, continuar y no mostrar el comando en esta iteración
            continue;
        }

        // Leer y procesar comando
        std::string comando = InterfazConsola::leerComando();
        procesarComando(comando);

        // Verificar condiciones de victoria/derrota
        if (!habitacionActual->tieneEnemigos() && habitacionActual->getNombre() == "Puente de Mando") {
            InterfazConsola::mostrarTitulo(Mensajes::VICTORIA);
            juegoActivo = false;
        }
    }

    if (!jugador->estaVivo()) {
        InterfazConsola::mostrarTitulo(Mensajes::DERROTA);
    }
}

void Juego::procesarComando(const std::string& comando) {
    std::stringstream ss(comando);
    std::string accion, parametro;
    ss >> accion;

    // Leer el resto como parámetro (para nombres con espacios)
    if (ss.rdbuf()->in_avail() > 0) {
        std::getline(ss, parametro);
        // Eliminar espacio inicial si existe
        if (!parametro.empty() && parametro[0] == ' ') {
            parametro.erase(0, 1);
        }
    }

    // Convertir a mayúsculas solo la acción, NO el parámetro
    std::transform(accion.begin(), accion.end(), accion.begin(), ::toupper);

    if (accion == "MOVER" || accion == "IR") {
        procesarMovimiento(parametro);
    } else if (accion == "USAR") {
        procesarUsoItem(parametro);
    } else if (accion == "ESTADO") {
        jugador->mostrarEstado();
    } else if (accion == "INVENTARIO" || accion == "INV") {
        jugador->mostrarInventario();
    } else if (accion == "GUARDAR") {
        SistemaGuardado::guardarPartida("partida_guardada.txt", jugador, habitacionActual);
    } else if (accion == "AYUDA" || accion == "HELP") {
        mostrarAyuda();
    } else if (accion == "SALIR" || accion == "QUIT") {
        juegoActivo = false;
    } else if (accion == "RECOGER" || accion == "TOMAR") {
        procesarRecogerItem(parametro);
    } else {
        InterfazConsola::mostrarError(Mensajes::ERROR_COMANDO);
    }
}

void Juego::procesarMovimiento(const std::string& direccion) {
    std::string dirUpper = direccion;
    std::transform(dirUpper.begin(), dirUpper.end(), dirUpper.begin(), ::toupper);

    Direccion dir;

    if (dirUpper == "NORTE" || dirUpper == "N") dir = Direccion::NORTE;
    else if (dirUpper == "SUR" || dirUpper == "S") dir = Direccion::SUR;
    else if (dirUpper == "ESTE" || dirUpper == "E") dir = Direccion::ESTE;
    else if (dirUpper == "OESTE" || dirUpper == "O") dir = Direccion::OESTE;
    else {
        InterfazConsola::mostrarError("Dirección no válida. Usa: NORTE, SUR, ESTE, OESTE");
        return;
    }

    Habitacion* siguiente = habitacionActual->getSalida(dir);
    if (siguiente) {
        // Verificar si la habitación requiere llave
        if (siguiente->getRequiereLlave()) {
            if (jugador->tieneItem("Llave_Nivel_1")) {
                habitacionActual = siguiente;
                InterfazConsola::mostrarExito("Te mueves a: " + habitacionActual->getNombre());
            } else {
                InterfazConsola::mostrarError("La habitación está bloqueada. Necesitas una Llave de Nivel 1.");
            }
        } else {
            habitacionActual = siguiente;
            InterfazConsola::mostrarExito("Te mueves a: " + habitacionActual->getNombre());
        }
    } else {
        InterfazConsola::mostrarError(Mensajes::ERROR_DIRECCION);
    }
}

void Juego::procesarUsoItem(const std::string& nombreItem) {
    if (nombreItem.empty()) {
        InterfazConsola::mostrarError("Debes especificar un objeto. Ej: USAR Kit_Médico");
        return;
    }

    jugador->usarItem(nombreItem);
}

void Juego::procesarRecogerItem(const std::string& nombreItem) {
    if (nombreItem.empty()) {
        InterfazConsola::mostrarError("Debes especificar un objeto. Ej: RECOGER Kit_Médico");
        return;
    }

    // Buscar el objeto en la habitación actual
    auto& objetos = habitacionActual->getObjetos();
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if ((*it)->getNombre() == nombreItem) {
            jugador->agregarItem(*it);
            objetos.erase(it);
            std::cout << "¡Has recogido: " << nombreItem << "!" << std::endl;
            return;
        }
    }
    std::cout << "No hay ningún " << nombreItem << " en esta habitación." << std::endl;
}

void Juego::mostrarAyuda() {
    InterfazConsola::mostrarTitulo("AYUDA - COMANDOS DISPONIBLES");
    InterfazConsola::mostrarMensaje("MOVIMIENTO: MOVER NORTE, MOVER SUR, MOVER ESTE, MOVER OESTE");
    InterfazConsola::mostrarMensaje("OBJETOS: RECOGER [nombre_exacto], USAR [nombre_exacto], INVENTARIO");
    InterfazConsola::mostrarMensaje("NOMBRES EXACTOS: Kit_Médico, Linterna, Batería, Pistola_Láser, Traje_Reforzado, Llave_Nivel_1");
    InterfazConsola::mostrarMensaje("INFORMACIÓN: ESTADO, AYUDA");
    InterfazConsola::mostrarMensaje("SISTEMA: GUARDAR, SALIR");
}

void Juego::iniciarCombate() {
    auto& enemigos = habitacionActual->getEnemigos();
    if (enemigos.empty()) return;

    // Por simplicidad, combatimos con el primer enemigo
    Enemigo* enemigo = enemigos[0];

    InterfazConsola::mostrarTitulo("¡COMBATE INICIADO!");
    std::cout << "Te enfrentas a: " << enemigo->getNombre() << std::endl;

    while (jugador->estaVivo() && enemigo->estaVivo()) {
        // Mostrar estado del combate
        std::cout << "\n--- ESTADO DEL COMBATE ---" << std::endl;
        jugador->mostrarEstado();
        std::cout << " vs ";
        enemigo->mostrarEstado();
        std::cout << std::endl;

        // Turno del jugador
        std::cout << "\n¿QUÉ DESEAS HACER?" << std::endl;
        std::cout << "1. ATACAR | 2. USAR OBJETO | 3. HUIR" << std::endl;
        std::cout << "Elige una opción (1, 2, 3): ";

        std::string opcion;
        std::getline(std::cin, opcion);

        if (opcion == "1") {
            jugador->atacar(enemigo);
            if (!enemigo->estaVivo()) {
                std::cout << "¡Has derrotado a " << enemigo->getNombre() << "!" << std::endl;
                // Dar experiencia al jugador
                jugador->ganarExperiencia(enemigo->getExperienciaOtorgada());
                // Eliminar enemigo de la habitación
                habitacionActual->eliminarEnemigo(enemigo);
                break;
            }
        }
        else if (opcion == "2") {
            if (jugador->tieneItems()) {
                jugador->mostrarInventario();
                std::cout << "¿Qué objeto quieres usar? ";
                std::string item;
                std::getline(std::cin, item);
                jugador->usarItem(item);
            } else {
                std::cout << "No tienes objetos en el inventario." << std::endl;
            }
        }
        else if (opcion == "3") {
            std::cout << "Intentas huir del combate..." << std::endl;
            // 50% de probabilidad de huir
            if (rand() % 100 < 50) {
                std::cout << "¡Logras huir!" << std::endl;
                break;
            } else {
                std::cout << "¡No logras huir!" << std::endl;
            }
        }
        else {
            std::cout << "Opción no válida. Pierdes tu turno." << std::endl;
        }

        // Turno del enemigo (si sigue vivo)
        if (enemigo->estaVivo()) {
            std::cout << "\n--- TURNO DEL ENEMIGO ---" << std::endl;
            enemigo->atacar(jugador);

            // Verificar si el jugador murió
            if (!jugador->estaVivo()) {
                break;
            }
        }
    }
}