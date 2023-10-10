#ifndef _CEILING_H
#define _CEILING_H

#include "sphere.h"

/**
 * @brief The _ceiling class
 * Shapes the top of the hierarchical model.
 * It is a transformed instance of the sphere symbol.
 */
class _ceiling: public _object3D
{
public:
    _sphere* Sphere; /**< Symbol */

    /**
     * @brief _ceiling Default constructor
     */
    _ceiling();

    /**
     * @brief draw Redefined inherited method where modeling
     * transformations to symbols and instances are applied
     * @param mode drawing mode
     */
    void draw(int mode);
};

#endif // _CEILING_H
