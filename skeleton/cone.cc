#include "cone.h"

_cone::_cone(float r, float h)
{
    // Asigna los valores en valor absoluto (evita errores)
    Radius = abs(r);
    Height = abs(h);

    // Crea el perfil para generar el objeto por revolucion
    vector<_vertex3f> v0(3);
    v0[0] = _vertex3f(0, Height/2.0, 0);
    v0[1] = _vertex3f(Radius, -Height/2.0, 0);
    v0[2] = _vertex3f(0,-Height/2.0,0);

    this->generate_revolution_object(36,v0);
    this->calculateNormalTriangles();
    this->calculateNormalVertices();
}
