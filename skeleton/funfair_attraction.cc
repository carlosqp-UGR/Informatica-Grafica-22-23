#include "funfair_attraction.h"

_funfair_attraction::_funfair_attraction()
{
    RtBase = new _rotatory_base();
}

void _funfair_attraction::draw(int mode) {

    // Pintamos la base rotatoria
    glPushMatrix();
        glTranslatef(0,2,0);
        // (*) Podríamos aplicar aquí la rotacion 3er grado libertad
        glRotatef(getBeta(),0,1,0);
        RtBase->draw(mode);
    glPopMatrix();

    // Pintamos la base estática
    glPushMatrix();
        glTranslatef(0,1,0);
        glScalef(8,2,8);
        RtBase->Arm->Cylinder->draw(mode);
    glPopMatrix();
}


/** Methods to modify first degree of freedom **/

float _funfair_attraction::getSigma() {
    return RtBase->Arm->getSigma();
}

bool _funfair_attraction::increaseSigma() {
    return RtBase->Arm->increaseSigma();
}

bool _funfair_attraction::decreaseSigma() {
    return RtBase->Arm->decreaseSigma();
}

bool _funfair_attraction::increaseSigmaVelocity() {
    return RtBase->Arm->increaseSigmaVelocity();
}

bool _funfair_attraction::decreaseSigmaVelocity() {
    return RtBase->Arm->decreaseSigmaVelocity();
}

/** Methods to modify second degree of freedom **/
float _funfair_attraction::getAlpha() {
    return RtBase->Arm->getAlpha();
}

bool _funfair_attraction::increaseAlpha() {
    return RtBase->Arm->increaseAlpha();
}

bool _funfair_attraction::decreaseAlpha() {
    return RtBase->Arm->decreaseAlpha();
}
bool _funfair_attraction::increaseAlphaVelocity() {
    return RtBase->Arm->increaseAlphaVelocity();
}

bool _funfair_attraction::decreaseAlphaVelocity() {
    return RtBase->Arm->decreaseAlphaVelocity();
}

/** Methods to modify third degree of freedom **/

float _funfair_attraction::getBeta() {
    return RtBase->getBeta();
}

bool _funfair_attraction::increaseBeta() {
    return RtBase->increaseBeta();
}

bool _funfair_attraction::decreaseBeta() {
    return RtBase->decreaseBeta();
}

bool _funfair_attraction::increaseBetaVelocity() {
    return RtBase->increaseBetaVelocity();
}

bool _funfair_attraction::decreaseBetaVelocity() {
    return RtBase->decreaseBetaVelocity();
}

/*
// Illumination-> Llamamos a los símbolos
void _funfair_attraction::draw_flat_lighting() {
    RtBase->Arm->Seat->Cube->draw_flat_lighting();
    RtBase->Arm->Cylinder->draw_flat_lighting();
    RtBase->Ceiling->Sphere->draw_flat_lighting();
}
void _funfair_attraction::draw_gouraud_lighting() {
    RtBase->Arm->Seat->Cube->draw_gouraud_lighting();
    RtBase->Arm->Cylinder->draw_gouraud_lighting();
    RtBase->Ceiling->Sphere->draw_gouraud_lighting();
}
*/




