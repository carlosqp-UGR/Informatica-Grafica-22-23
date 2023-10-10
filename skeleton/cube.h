#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"

/**
 * @brief The _cube class
 * Creates a cube object (defined by its side's size)
 * centered in the origin.
 */
class _cube:public _object3D
{
public:
    /**
     * @brief _cube Paramater and default constructor
     * @param Size Size of the cube's side
     * @pre Size>0
     */
    _cube(float Size=1.0);
};

#endif // CUBE_H
