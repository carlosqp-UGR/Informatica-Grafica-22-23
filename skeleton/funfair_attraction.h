#ifndef _FUNFAIR_ATTRACTION_H
#define _FUNFAIR_ATTRACTION_H

#include "rotatory_base.h"

/**
 * @brief The _funfair_attraction class
 * Hierarchical model. Represents a fun fair attraction.
 * Has 5 hierarchy levels and 3 degrees of freedom
 * (see scene graph PDF document).
 */
class _funfair_attraction: public _object3D
{
public:
    _rotatory_base* RtBase;     /**< hierarchical element immediatly below */

    /**
     * @brief _funfair_attraction Default constructor
     */
    _funfair_attraction();

    /**
     * @brief draw Redefined inherited method where modeling
     * transformations to symbols and instances are applied
     * @param mode drawing mode
     */
    void draw(int mode);

    /**< Methods to modify first degree of freedom */

    /**
     * @brief getSigma
     * @return Sigma value: 1st degree of freedom
     */
    float getSigma();

    /**
     * @brief increaseSigma increases Sigma by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool increaseSigma();

    /**
     * @brief decreaseSigma decreases Sigma by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool decreaseSigma();

    /**
     * @brief increaseSigmaVelocity increases the velocity (modification rate)
     * of Sigma
     * @return true if the action is completed, false instead
     */
    bool increaseSigmaVelocity();

    /**
     * @brief decreaseSigmaVelocity decreases the velocity (modification rate)
     * of Sigma
     * @return true if the action is completed, false instead
     */
    bool decreaseSigmaVelocity();

    /**< Methods to modify second degree of freedom */

    /**
     * @brief getAlpha
     * @return Alpha value: 2nd degree of freedom
     */
    float getAlpha();

    /**
     * @brief increaseAlpha increases Alpha by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool increaseAlpha();

    /**
     * @brief decreaseAlpha decreases Alpha by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool decreaseAlpha();

    /**
     * @brief increaseAlphaVelocity increases the velocity factor
     * (modification rate) of Alpha
     * @return true if the action is completed, false instead
     */
    bool increaseAlphaVelocity();

    /**
     * @brief decreaseAlphaVelocity decreases the velocity factor
     * (modification rate) of Alpha
     * @return true if the action is completed, false instead
     */
    bool decreaseAlphaVelocity();

    /**< Methods to modify third degree of freedom */

    /**
     * @brief getBeta
     * @return Beta value: 3rd degree of freedom
     */
    float getBeta();

    /**
     * @brief increaseBeta increases Beta by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool increaseBeta();

    /**
     * @brief decreaseBeta decreases Beta by its velocity factor
     * @return true if the action is completed, false instead
     */
    bool decreaseBeta();

    /**
     * @brief increaseBetaVelocity increases the velocity factor
     * (modification rate) of Beta
     * @return true if the action is completed, false instead
     */
    bool increaseBetaVelocity();

    /**
     * @brief decreaseBetaVelocity decreases the velocity factor
     * (modification rate) of Beta
     * @return true if the action is completed, false instead
     */
    bool decreaseBetaVelocity();
};

#endif // _FUNFAIR_ATTRACTION_H
