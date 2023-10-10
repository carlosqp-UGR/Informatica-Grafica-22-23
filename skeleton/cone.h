#ifndef CONE_H
#define CONE_H

#include "revolution_object.h"

/**
 * @brief The _cone class
 * Creates a cone (defined by its height and radius)
 * centered in the origin. Created by the revolution
 * method (Y axis).
 */
class _cone : public _revolution_object
{
private:
    float Radius;
    float Height;
public:
    /**
     * @brief _cone Constructor
     * @param r Radius from cone object
     * @param h Height from cone object
     * @pre r>0
     * @pre h>0
     */
    _cone(float r=0.5, float h=1.0);
};

#endif // CONE_H
