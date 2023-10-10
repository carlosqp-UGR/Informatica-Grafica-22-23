#include "ply_revolution_object.h"

_ply_revolution_object::_ply_revolution_object(int n, const string &file_name)
{
    // Lee y carga el fichero .ply (contiene el perfil)
    vector<_vertex3f> profile;
    _ply_object ply (file_name);
    profile = ply.Vertices;

    // Carga el perfil y lo genera
    this->generate_revolution_object(n,profile);

    // Calcula las normales para iluminación
    this->calculateNormalTriangles();
    this->calculateNormalVertices();

}   // Destruye las variables auxiliares (llama al destructor por defecto)
