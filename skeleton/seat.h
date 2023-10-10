#ifndef _SEAT_H
#define _SEAT_H

#include "cube.h"

/**
 * @brief The _seat class
 * Forms the most simple part of the hierarchical model.
 * Composed of a symbol
 */
class _seat: public _object3D
{
public:
    _cube* Cube;    /**< Symbol */

    /**
     * @brief _seat
     * Constructor, initializes the symbol
     */
    _seat();

    /**
     * @brief draw Redefined inherited method where modeling
     * transformations to symbols and instances are applied
     * @param mode drawing mode
     */
    void draw(int mode);
};

#endif // _SEAT_H
