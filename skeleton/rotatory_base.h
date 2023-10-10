#ifndef _ROTATORY_BASE_H
#define _ROTATORY_BASE_H

#include "ceiling.h"
#include "mechanical_arm.h"

/**
 * @brief The _rotatory_base class
 * Forms the rotatory base of the hierarchical model.
 * Composed of the ceiling, the arm and a cylinder(symbol).
 * Has a degree of freedom associated.
 */
class _rotatory_base: public _object3D
{
private:
    /**< Variables related to 3rd degree of freedom */
    float Beta;
    const float MinBetaVelocity = 1.0;
    const float MaxBetaVelocity = 36.0;
    float BetaVelocity;

public:
    _ceiling* Ceiling;                  /**< Next descendant part of the graph */
    _mechanical_arm* Arm;               /**< Next descendant part of the graph, contains the cylinder symbol */

    /**
     * @brief _rotatory_base
     * constructor, initializes both the ceiling and the arm
     */
    _rotatory_base();

    /**
     * @brief draw Redefined inherited method where modeling
     * transformations to symbols and instances are applied
     * @param mode drawing mode
     */
    void draw(int mode);

    /**< Methods to get and modify the variables related to the 3rd degree of freedom */

    /**
     * @brief getBeta
     * @return beta value
     */
    float getBeta();

    /**
     * @brief increaseBeta
     * @return true if the action is completed, false instead
     */
    bool increaseBeta();

    /**
     * @brief decreaseBeta
     * @return true if the action is completed, false instead
     */
    bool decreaseBeta();

    /**
     * @brief increaseBetaVelocity
     * @return true if the action is completed, false instead
     */
    bool increaseBetaVelocity();

    /**
     * @brief decreaseBetaVelocity
     * @return true if the action is completed, false instead
     */
    bool decreaseBetaVelocity();

};

#endif // _ROTATORY_BASE_H
