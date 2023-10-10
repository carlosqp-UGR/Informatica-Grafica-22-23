#include "mechanical_arm.h"

_mechanical_arm::_mechanical_arm()
{
    Seat = new _seat();
    Cylinder = new _cylinder();
    Sigma = 1.0;
    Alpha = 0.0;
    SigmaVelocity = 0.1;
    AlphaVelocity = 1.0;
}

void _mechanical_arm::draw(int mode) {

    // Ya no es necesaria la siguiente línea, lo hemos indicado antes en _seat
    // glMatrixMode(GL_MODELVIEW_MATRIX);

    /*  ¿¿??
    glPushMatrix();
        // (*) En este punto debemos aplicar el segundo grado de libertad para rotar todo el brazo
        // Otra opción (preferible) es aplicarla en el siguiente elemento de la jerarquía
        glRotatef(alpha,0,0,1);
    glPopMatrix(); // Esta sentencia iría al final del método
    */

// Pintamos primeramente el brazo
    glPushMatrix();
        glTranslatef(2*getSigma(),0,0);
        // (*) En este punto debemos aplicar el primer grado de libertad para escalar el tamaño del brazo mecánico
        glScalef(4*getSigma(),1,1);
        glRotatef(90,0,0,1);
        this->Cylinder->draw(mode);

    // Restauramos el contenido original de la pila
    glPopMatrix();

// Pintamos después el asiento bien colocado en este
    glPushMatrix();
        // Se debe trasladar el objeto 4(largo original)*factor de escala
        glTranslatef(4*getSigma(),0.5,0);
        Seat->draw(mode);
    glPopMatrix();

}

/** 1st degree of freedom **/
float _mechanical_arm::getSigma() {
    return Sigma;
}

bool _mechanical_arm::increaseSigma() {
    if (MinSigma<=(Sigma+SigmaVelocity) && (Sigma+SigmaVelocity)<=MaxSigma) {
        Sigma += SigmaVelocity;
        return true;
    } else
        return false;
}

bool _mechanical_arm::decreaseSigma() {
    if (MinSigma<=(Sigma-SigmaVelocity) && (Sigma-SigmaVelocity)<=MaxSigma) {
        Sigma -= SigmaVelocity;
        return true;
    } else
        return false;
}

bool _mechanical_arm::increaseSigmaVelocity() {
    float factor = 0.05;
    if ( MinSigmaVelocity<=(SigmaVelocity+factor) && (SigmaVelocity+factor)<=MaxSigmaVelocity  ) {
        SigmaVelocity+=factor;
        return true;
    } else
        return false;
}

bool _mechanical_arm::decreaseSigmaVelocity() {
    float factor = 0.05;
    if ( MinSigmaVelocity<=(SigmaVelocity-factor) && (SigmaVelocity-factor)<=MaxSigmaVelocity  ) {
        SigmaVelocity-=factor;
        return true;
    } else
        return false;
}

/** 2nd degree of freedom **/
float _mechanical_arm::getAlpha() {
    return Alpha;
}

bool _mechanical_arm::increaseAlpha() {
    if( MinAlpha<=(Alpha+AlphaVelocity) && (Alpha+AlphaVelocity)<=MaxAlpha ) {
        Alpha += AlphaVelocity;
        return true;
    } else
        return false;
}

bool _mechanical_arm::decreaseAlpha() {
    if( MinAlpha<=(Alpha-AlphaVelocity) && (Alpha-AlphaVelocity)<=MaxAlpha ) {
        Alpha -= AlphaVelocity;
        return true;
    } else
        return false;
}

bool _mechanical_arm::increaseAlphaVelocity() {
    float factor = 0.5;
    if ( MinAlphaVelocity<=(AlphaVelocity+factor) && (AlphaVelocity+factor)<=MaxAlphaVelocity  ) {
        AlphaVelocity+=factor;
        return true;
    } else
        return false;
}

bool _mechanical_arm::decreaseAlphaVelocity() {
    float factor = 0.5;
    if ( MinAlphaVelocity<=(AlphaVelocity-factor) && (AlphaVelocity-factor)<=MaxAlphaVelocity  ) {
        AlphaVelocity-=factor;
        return true;
    } else
        return false;
}
