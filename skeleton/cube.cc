#include "cube.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube::_cube(float Size) {
    // Un cubo está compuesto por 8 vértices
    Vertices.resize(8);
    Vertices[0] = _vertex3f(-Size/2, -Size/2, Size/2);  // A
    Vertices[1] = _vertex3f(Size/2, -Size/2, Size/2);   // B
    Vertices[2] = _vertex3f(Size/2, -Size/2, -Size/2);  // C
    Vertices[3] = _vertex3f(-Size/2, -Size/2, -Size/2); // D
    Vertices[4] = _vertex3f(-Size/2, Size/2, Size/2);   // E
    Vertices[5] = _vertex3f(Size/2, Size/2, Size/2);    // F
    Vertices[6] = _vertex3f(Size/2, Size/2, -Size/2);   // G
    Vertices[7] = _vertex3f(-Size/2, Size/2, -Size/2);  // H

    // La superficie del cubo son 6 caras, cada una formado por dos triángulos,
    // por lo que está compuesta por 12 triángulos.
    // Definimos los triángulos en sentido antihorario
    Triangles.resize(12);
    Triangles[0]=_vertex3ui(4,1,5); // EBF  (4,1,5)
    Triangles[1]=_vertex3ui(4,0,1); // EAB  (4,0,1)
    Triangles[2]=_vertex3ui(5,2,6); // FCG  (5,2,6)
    Triangles[3]=_vertex3ui(5,1,2); // FBC  (5,1,2)
    Triangles[4]=_vertex3ui(6,3,7); // GDH  (6,3,7)
    Triangles[5]=_vertex3ui(6,2,3); // GCD  (6,2,3)
    Triangles[6]=_vertex3ui(7,0,4); // HAE  (7,0,4)
    Triangles[7]=_vertex3ui(7,3,0); // HDA  (7,3,0) *
    Triangles[8]=_vertex3ui(0,2,1); // ACB  (0,2,1)
    Triangles[9]=_vertex3ui(0,3,2); // ADC  (0,3,2)
    Triangles[10]=_vertex3ui(7,5,6); // HFG  (7,5,6)
    Triangles[11]=_vertex3ui(7,4,5); // HEF  (7,4,5)


    // Calculamos y rellenamos las normales para la iluminación
    this->calculateNormalTriangles();
    // this->calculateNormalVertices_inefficient();
    this->calculateNormalVertices();
}
