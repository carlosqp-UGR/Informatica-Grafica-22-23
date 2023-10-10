#include "cylinder.h"

_cylinder::_cylinder(float r, float h)
{
    float Radius = abs(r);
    float Height = abs(h);

    // Crea el perfil para generar el objeto por revolucion
    vector<_vertex3f> v1(4);
    v1[0] = _vertex3f(0, Height/2.0, 0);
    v1[1] = _vertex3f(Radius, Height/2.0,0);
    v1[2] = _vertex3f(Radius, -Height/2.0,0);
    v1[3] = _vertex3f(0, -Height/2.0, 0);

    // Creamos el objeto por revolucion y lo guardamos
    this->generate_revolution_object(36, v1);
    this->calculateNormalTriangles();
    this->calculateNormalVertices();
}
