#include "seat.h"

_seat::_seat()
{
    this->Cube = new _cube();
}

// Principio de diseño: construimos partiendo del objeto más pequeño en la
// jerarquía para después crear el resto de objetos dependientes a partir
// de este.

// ¿Símbolo e instancia?
void _seat::draw(int mode) {

// Como este es el primer objeto en ser modelado, debemos añadir la siguiente
// línea que indica que todas las transformaciones aplicadas a partir de ahora
// se deben realizar en la matriz modelado-vista
    glMatrixMode(GL_MODELVIEW_MATRIX);

    // Copiamos el contenido de la matriz en la pila y lo salvamos
    glPushMatrix();

        // Realizamos las transformaciones necesarias ¡¡Comportamiento de Pila!!
        glScalef(2,2,3);

        // Pintamos la instancia del cubo
        this->Cube->draw(mode);

    // Restauramos el contenido original de la pila
    glPopMatrix();
}
