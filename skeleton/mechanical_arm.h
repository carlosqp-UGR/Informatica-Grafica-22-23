#ifndef _MECHANICAL_ARM_H
#define _MECHANICAL_ARM_H

#include "seat.h"
#include "cylinder.h"

/**
 * @brief The _mechanical_arm class
 * Forms the arm of the hierarchical model.
 * Composed of a seat and a cylinder(symbol).
 * Has two different degrees of freedom associated.
 */
class _mechanical_arm: public _object3D
{
private:
    /**< Variables related to 1st and 2nd degrees of freedom **/
    const float MinSigma = 1.0;
    const float MaxSigma = 2.0;
    const float MinSigmaVelocity = 0.05;
    const float MaxSigmaVelocity = 0.5;

    const float MinAlpha = -25.0;
    const float MaxAlpha = 30.0;
    const float MinAlphaVelocity = 0.5;
    const float MaxAlphaVelocity = 15.0;

    float Sigma; // 1.0 <= sigma <= 2.0
    float Alpha;  // -25 <= alpha <= 30

    float SigmaVelocity;    /**< Controls the rate of modification of the 1st degree of freedom */
    float AlphaVelocity;    /**< Controls the rate of modification of the 2nd degree of freedom */

public:                     /**< Public visibility in order to access the symbol if necessary */
    _seat* Seat;            /**< seat element, previous element in the graph */
    _cylinder* Cylinder;    /**< symbol */

    /**
     * @brief _mechanical_arm
     * constructor, initializes both the seat and the symbol
     */
    _mechanical_arm();

    /**
     * @brief draw Redefined inherited method where modeling
     * transformations to symbols and instances are applied
     * @param mode drawing mode
     */
    void draw(int mode);

    /**< Methods to modify first degree of freedom **/
    float getSigma();
    bool increaseSigma();
    bool decreaseSigma();
    bool increaseSigmaVelocity();
    bool decreaseSigmaVelocity();

    /** Methods to modify second degree of freedom **/
    float getAlpha();
    bool increaseAlpha();
    bool decreaseAlpha();
    bool increaseAlphaVelocity();
    bool decreaseAlphaVelocity();

};

#endif // _MECHANICAL_ARM_H
