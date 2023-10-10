#ifndef _LIGHTS_H
#define _LIGHTS_H

#include <GL/gl.h>  // glLightfv(), glEnable()
#include "vertex.h"

/**
 * @brief The _lights class
 * Controls the lights required for P4.
 */
class _lights
{
private:
    _vertex4f pos_light0;   /**< Position of the 1st light (at infinite) */
    _vertex4f pos_light1;   /**< Initial position of the 2nd light */
    float angle_light1;     /**< Rotation angle for the animation of the 2nd light */
public:

    /**
     * @brief _lights Default constructor
     */
    _lights();

    /**
     * @brief enableLight0 Activates 1st (white) light
     */
    inline void enableLight0() {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION,(GLfloat *) &pos_light0);
    }

    /**
     * @brief disableLight0 Deactivates 1st light
     */
    inline void disableLight0() {
        glDisable(GL_LIGHT0);
    }

    /**
     * @brief enableLight1 Activates 2nd (magenta) light
     */
    void enableLight1();

    /**
     * @brief disableLight1 Deactivates 2nd light
     */
    inline void disableLight1() {
        glDisable(GL_LIGHT1);
    }

    /**
     * @brief rotateLight1 Modifies the angle of rotation of the 2nd
     * light.
     */
    inline void rotateLight1() {angle_light1+=40;};
};

#endif // _LIGHTS_H
