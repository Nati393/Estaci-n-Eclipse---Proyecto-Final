#ifndef MENSAJES_H
#define MENSAJES_H

#include <string>

namespace Mensajes {
    // Mensajes del juego
    const std::string BIENVENIDA = "ESTACIÓN ECLIPSE - SISTEMA DE EMERGENCIA ACTIVADO";
    const std::string DESCRIPCION_JUEGO = "Eres Leia Jemison, ingeniera de sistemas. La estación está en silencio...";
    const std::string COMANDOS_DISPONIBLES = "Comandos: MOVER [dirección], USAR [item], ATACAR, ESTADO, INVENTARIO, GUARDAR, SALIR";
    const std::string VICTORIA = "¡HAS RESTAURADO EL CONTROL DE LA ESTACIÓN ECLIPSE! Misión cumplida.";
    const std::string DERROTA = "La oscuridad te envuelve... La estación ECLIPSE permanece en silencio eterno.";
    
    // Mensajes de error
    const std::string ERROR_COMANDO = "Comando no reconocido. Usa AYUDA para ver comandos disponibles.";
    const std::string ERROR_DIRECCION = "No puedes moverte en esa dirección.";
    const std::string ERROR_ITEM = "No tienes ese objeto en el inventario.";
}

#endif