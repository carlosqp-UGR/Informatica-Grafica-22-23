#ifndef SPHERE_H
#define SPHERE_H

#include "revolution_object.h"

/**
 * @brief The _sphere class
 * Creates a sphere (defined by radius)
 * centered in the origin.
 * Created by the revolution method (Y axis).
 */
class _sphere : public _revolution_object
{
private:
    float Radius;
public:

    /**
     * @brief _sphere Constructor
     * @param r
     */
    _sphere(float r=0.5);

    /**
     * @brief calculateNormalTriangle
     * calculates the normal of each triangle efficiently for the sphere
     * @pre requieres the vertex's normals calculated before
     */
    void calculateNormalTriangle();

    /**
     * @brief calculateNormalVertices
     * calculates the normal of each vertex efficiently: the normal of
     * each vertex is the vector formed by the origin and the vertex.
     */
    void calculateNormalVertices();
};

#endif // SPHERE_H
