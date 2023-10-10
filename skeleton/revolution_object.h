#ifndef _REVOLUTION_OBJECT_H
#define _REVOLUTION_OBJECT_H

#include "object3d.h"
#include <cmath>

// Debemos definir la herencia como 'virtual' para evitar ambigüedades en
// su clase hija _ply_revolution_object (ocurre el problema del diamante
// al heredar de dos clases -> _ply_object y _revolution_object y tener
// el mismo abuelo -> _object3D).

/**
 * @brief The _revolution_object class
 * Implemented as an interface class; only adds functionalities.
 */
class _revolution_object: virtual public _object3D {
public:

    /**
     * @brief generates a revolution object based on a profile
     * @param n natural number of subdivisions/ new profiles generated
     * @param profile array of vertexes representing the generating curve
     */
    void generate_revolution_object(unsigned int n, const vector<_vertex3f> &profile);

    /**
     * @brief generates a revolution object based on a profile (inefficiently)
     * @param n natural number of subdivisions/ new profiles generated
     * @param profile array of vertexes representing the generating curve
     */
    void generate_revolution_object_inefficient(unsigned int n, const vector<_vertex3f> &profile);
};

#endif // _REVOLUTION_OBJECT_H
