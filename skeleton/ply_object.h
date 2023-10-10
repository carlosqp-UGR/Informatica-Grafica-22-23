#ifndef PLY_OBJECT_H
#define PLY_OBJECT_H

#include "object3d.h"
#include "file_ply_stl.h"

// Debemos definir la herencia como 'virtual' para evitar ambigüedades en
// su clase hija _ply_revolution_object (ocurre el problema del diamante
// al heredar de dos clases -> _ply_object y _revolution_object y tener
// el mismo abuelo -> _object3D).

/**
 * @brief The _ply_object class
 * Processes a ply file and converts it into an object 3d
 */
class _ply_object: virtual public _object3D {
private:
    _file_ply file; /**< file which contains the object */

public:
    /**
     * @brief _PLY_object constructor
     * @param file_name path of the .ply file which contains the 3d object
     */
    _ply_object(const string &file_name = "../ply_models/beethoven.ply");
};

#endif // PLY_OBJECT_H
