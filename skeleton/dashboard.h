#ifndef _DASHBOARD_H
#define _DASHBOARD_H

// #include "object3d.h"
#include "tex_object3d.h"

/**
 * @brief The _dashboard class
 * XY plane centered at origin with NxN squares.
 * Has a texture attached to it.
 */
class _dashboard: public _tex_object3D
{
private:
    unsigned int N; /**< Number of squares/cuts of the dashboard */
    float Size;     /**< Size of the dashboard */
public:
    /**
     * @brief _chessboard Parameter and default constructor
     * @param n Number of squares/cuts of the dashboard
     * @param _size Size of the dashboard
     * @pre n>0
     * @pre size>0
     */
    _dashboard(unsigned int n=5, float size=10.0);

    /**
     * @brief calculateTexCoords Overriden abstract method
     * Calculates the texture coordinates for the dashboard
     */
    void calculateTexCoords() override;
};

#endif // _DASHBOARD_H
