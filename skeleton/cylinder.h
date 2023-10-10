#ifndef CYLINDER_H
#define CYLINDER_H

#include "revolution_object.h"

/**
 * @brief The _cylinder class
 * Creates a cylinder (defined by its height and radius)
 * centered in the origin. Created by the revolution
 * method (Y axis).
 */
class _cylinder : public _revolution_object
{
private:
    float Height;
    float Radius;
public:
    /**
     * @brief _cylinder Default and parameter constructor
     * @param r Radius
     * @param h Height
     * @pre r>0
     * @pre h>0
     */
    _cylinder(float r=0.5, float h=1.0);
};

#endif // CYLINDER_H
