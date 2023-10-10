#include "sphere.h"

_sphere::_sphere(float r)
{
    this->Radius = abs(r);

    // Generamos el perfil del semicirculo sobre el plano XY
    int n = 10;
    const double Alpha = M_PI/(2.0*n);
    vector<_vertex3f> v0 (2*n+1);
    int cont = 0;

    for(int i=n; i>=-n; --i) {
        float x = cos(i*Alpha)*Radius;
        float y = sin(i*Alpha)*Radius;
        v0[cont] = _vertex3f(x,y,0);
        cont++;
    }

    // El primer y último punto están en el eje. Para que la comparación en el
    // método de generar objeto por revolucion (x==0 y z==0) sea exacta, insertamos
    // a mano estos valores en el perfil.
    v0[0] = _vertex3f(0,Radius,0);
    v0[v0.size()-1] = _vertex3f(0,-Radius,0);

    // LLamamos al método heredado que nos genera el obj por revolución
    this->generate_revolution_object(36,v0);

    // Calcula las normales para iluminación (métodos propios)
    calculateNormalVertices();
    calculateNormalTriangles();
}

/*****************************************************************************//*
 *
 *
 *
 *****************************************************************************/
// Calcula de forma eficiente la normal de los triángulos.Esto lo hace simplemente con
// el centro de la esfera (el origen) y el vértice (esa es la normal del vértice)
void _sphere::calculateNormalVertices() {
    // Método eficiente; calcula la normal del vértice: esta es el vector que forma el propio
    // vértice con el centro de la esfera.
    NormalVertices.clear();
    NormalVertices.resize(Vertices.size());

    for(unsigned int i=0; i<Vertices.size(); ++i) {
        _vertex3f normal = Vertices[i];     // Vi - 0
        NormalVertices[i] = normal.normalize();
    }
}

/*****************************************************************************//*
 *
 *
 *
 *****************************************************************************/
// Calcula de forma eficiente la normal de los triángulos.Esto lo hace simplemente con
// el centro de la esfera (el origen) y el vértice (esa es la normal del vértice)
void _sphere::calculateNormalTriangle() {

    // Evitamos el error, para calcularlo de forma eficiente necesitamos antes los vértices
    if(NormalVertices.empty())
        calculateNormalVertices();

    // Método eficiente; la normal del triángulo es la media aritmética de las tres normales
    // de los tres vértices que la componen
    NormalTriangles.clear();
    NormalTriangles.resize(Triangles.size());
    for(unsigned int i=0; i<Triangles.size(); ++i) {
        _vertex3f normal = (NormalVertices[Triangles[i][0]] + NormalVertices[Triangles[i][1]] + NormalVertices[Triangles[i][2]])/3.0;
        NormalTriangles[i] = normal.normalize();
    }
}

