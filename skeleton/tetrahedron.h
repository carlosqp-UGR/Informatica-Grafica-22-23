/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "object3d.h"

/**
 * @brief The _tetrahedron class
 * Creates a tetrahedron object centered at origin.
 * Vertexes and triangles defined manually.
 */
class _tetrahedron:public _object3D {
public:
    /**
     * @brief _tetrahedron default and parameters' constructor
     * @param Size
     */
    _tetrahedron(float Size=1.0);
};

#endif
