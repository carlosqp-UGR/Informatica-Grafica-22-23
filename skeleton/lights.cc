#include "lights.h"
#include "colors.h"

_lights::_lights() {
    // Definimos el color de la luz 1. La luz 0 es blanca por defecto.
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat*)&_colors_ne::MAGENTA);
    glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat*)&_colors_ne::MAGENTA);

    // Definimos las posiciones de la luz, las necesitaremos cuando queramos activarlas.
    pos_light0 = _vertex4f(0,0,50,0);  // w==0 -> infinito
    // pos_light0 = _vertex4f(0,2,0,0);  // w==0 -> infinito
    pos_light1 = _vertex4f(-15,0,0,1);  // w!=0 -> no infinito
}

void _lights::enableLight1() {
    // La luz 1 rotará alrededor del eje Y.
    // Aplicamos una rotación a la matriz modelview antes de activarla para que rote.
    glEnable(GL_LIGHT1);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix();
        glRotatef(angle_light1,0,1,0);
        glLightfv(GL_LIGHT1, GL_POSITION,(GLfloat *) &pos_light1);
    glPopMatrix();
}
