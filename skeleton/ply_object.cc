#include "ply_object.h"

_ply_object::_ply_object(const string &file_name) : file()
{
    // Abre el fichero (comprueba si lo ha podido abrir)
    if (file.open(file_name)==1) {
        // Lee el fichero .ply y almacena los datos leidos (parcialmente)
        vector<float> Coordinates;
        vector<unsigned int> Positions;
        file.read(Coordinates, Positions);
        file.close();

        // Convertimos los datos leidos en vértices y triángulos
        Vertices.clear();
        Vertices.resize(Coordinates.size()/3);
        for(unsigned int i=0; i<Vertices.size(); ++i) {
            Vertices[i] = _vertex3f(Coordinates[3*i],Coordinates[3*i+1],Coordinates[3*i+2]);
        }

        Triangles.clear();
        Triangles.resize(Positions.size()/3);
        for(unsigned int j=0; j<Triangles.size(); ++j) {
            Triangles[j] = _vertex3ui(Positions[3*j],Positions[3*j+1],Positions[3*j+2]);
        }

        // Calcula las normales para iluminación
        this->calculateNormalTriangles();
        this->calculateNormalVertices();
    }
}
