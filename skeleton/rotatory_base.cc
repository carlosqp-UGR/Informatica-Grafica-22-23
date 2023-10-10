#include "rotatory_base.h"

_rotatory_base::_rotatory_base()
{
    Ceiling = new _ceiling();
    Arm = new _mechanical_arm();
    Beta = 0;
    BetaVelocity = 20;
}

void _rotatory_base::draw(int mode) {
    /*
    glPushMatrix();
        // (*) Aplicar aquí la rotacion 3er grado libertad, o en la siguiente pieza
        glRotatef(Beta,0,1,0);
    glPopMatrix(); // Esta sentencia iría al final del método
    */

// Modelamos el brazo
    glPushMatrix();
        glTranslatef(1,2.5,0);
        // (*) Podemos aplicar aquí el 2o gr de libertad, rotacion del brazo eje Z
        glRotatef(Arm->getAlpha(),0,0,1);
        Arm->draw(mode);
    glPopMatrix();

// Modelamos la base giratoria
    glPushMatrix();
        glTranslatef(0,2.5,0);
        glScalef(4,5,4);
        Arm->Cylinder->draw(mode);
    glPopMatrix();

    // Modelamos el techo
    glPushMatrix();
        glTranslatef(0,7,0);
        Ceiling->draw(mode);
    glPopMatrix();
}

/** 3rd degree of freedom **/
float _rotatory_base::getBeta() {
    return Beta;
}

bool _rotatory_base::increaseBeta() {
//   if( MinBeta<=(Beta+BetaVelocity) && (Beta+BetaVelocity)<=MaxBeta )
    Beta += BetaVelocity;
    return true;
}

bool _rotatory_base::decreaseBeta() {
//    if( MinBeta<=(Beta-BetaVelocity) && (Beta-BetaVelocity)<=MaxBeta )
    Beta -= BetaVelocity;
    return true;
}

bool _rotatory_base::increaseBetaVelocity() {
    float factor = 6.0;
    if ( MinBetaVelocity<=(BetaVelocity+factor) && (BetaVelocity+factor)<=MaxBetaVelocity ) {
        BetaVelocity += factor;
        return true;
    } else
        return false;
}

bool _rotatory_base::decreaseBetaVelocity() {
    float factor = 6.0;
    if ( MinBetaVelocity<=(BetaVelocity-factor) && (BetaVelocity-factor)<=MaxBetaVelocity ) {
        BetaVelocity -= factor;
        return true;
    } else
        return false;
}





