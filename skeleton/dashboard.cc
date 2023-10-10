#include "dashboard.h"

_dashboard::_dashboard(unsigned int n, float size)
{
    N = n;
    Size = size;

    // Crearemos un plano XY con n*n casillas y (n+1)*(n+1) vértices centrado en el origen

    // Generamos los vértices
    Vertices.clear();
    Vertices.resize((N+1)*(N+1));

    // Empezamos en el vértice inferior izquierda y a partir de este
    // hacemos un barrido por alto (columnas, aumentando y) en el bucle
    // exterior y un barrido por ancho (filas, aumentando x) en el interior
    unsigned int i=0;
    for(unsigned int c=0; c<=N; ++c) {
        for(unsigned int r=0; r<=N; ++r) {
            Vertices[i].x = -Size/2.0 + c*Size/(float)N;    // Incrementamos x
            Vertices[i].y = -Size/2.0 + r*Size/(float)N;     // Incrementamos y
            Vertices[i].z = 0.0;;     // Decrementamos z
            i++;
        }
    }

    // Generamos los triángulos, en sentido antihorario. Similar a como se
    // generaban las mallas en el método por revolución
    Triangles.clear();
    Triangles.resize(N*N*2);
    // Pasar de coordenadas 2d a 1d: Vertices[r][c] = Vertices[r+c*(n+1)]
    unsigned int j=0;
    for(unsigned int c=0; c<N; ++c) {
        for(unsigned int r=0; r<N; ++r) {
            // Sentido antihorario:
            // Ta = ([r,c], [r+1,c+1], [r+1,c])
            Triangles[j++] = _vertex3ui( r+c*(N+1),
                                         r+1+((c+1)*(N+1)),
                                         r+1+c*(N+1) );

            // Tb = ([r,c], [r,c+1], [r+1,c+1])
            Triangles[j++] = _vertex3ui( r+c*(N+1),
                                         r+((c+1)*(N+1)),
                                         r+1+((c+1)*(N+1)) );
        }
    }

    // Calculamos sus normales  (Todas van a ser iguales)
    calculateNormalTriangles();
    calculateNormalVertices();

    // Cargamos y procesamos la imagen
    loadTexture("../textures/chessboard.jpg");

    // Calculamos las coordenadas de textura
    calculateTexCoords();

}

// Calcular
void _dashboard::calculateTexCoords() {
    TexCoords.clear();
    TexCoords.resize(Vertices.size());

    // Empezamos en el vértice inferior izquierda (0,0) y a partir de este
    // hacemos un barrido por alto (columnas, aumentando y +=size/n) en el bucle
    // exterior y un barrido por ancho (filas, aumentando x +=size/n) en el interior
    unsigned int i=0;
    for(unsigned int c=0; c<=N; ++c) {
        for(unsigned int r=0; r<=N; ++r) {
            TexCoords[i].x = c/(float)N;    // Incrementamos x
            TexCoords[i].y = r/(float)N;     // Incrementamos y
            i++;
        }
    }
}
