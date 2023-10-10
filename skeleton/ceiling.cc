#include "ceiling.h"

_ceiling::_ceiling()
{
    Sphere = new _sphere();
}

void _ceiling::draw(int mode) {
    glPushMatrix();
        glScalef(4,4,4);
        Sphere->draw(mode);
    glPopMatrix();
}
