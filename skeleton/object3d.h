/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"
#include "material.h"

/**
 * @brief The _object3D class
 * Basic class which contains the data structures and methods
 * required to create, visualize and store objects.
 */
class _object3D:public _basic_object3D {
public:
    vector<_vertex3ui> Triangles;         /**< Stores the surface of the object */
    vector<_vertex3f> NormalTriangles;    /**< Stores the NORMALIZED normal vector of each triangle (required for flat illum) */
    vector<_vertex3f> NormalVertices;     /**< Stores the NORMALIZED normal vector of each vertex (required for smooth illum) */
    int pick_triangle = -1;               /**< Index required for pick functionality */

    /**
    * @brief draw_line draws the object's arista
    */
    void draw_line();

    /**
    * @brief draw_fill draws the object's surface in a plane color
    */
    void draw_fill();

    /**
    * @brief draw_chess draws the object's surface in alternate plane colors
    */
    void draw_chess();

    /**
    * @brief draw_selection draws each triangle of the object's surface in a
    * unique/different color in order to pick it with the color pick method
    */
    void draw_selection();

    /**
    * @brief draw_flat_lighting draws the object with flat lighting
    * (needs a material in order to visualize it properly)
    */
    void draw_flat_lighting();

    /**
    * @brief draw_gouraud_lighting draws the object with smooth lighting
    * (needs a material in order to visualize it properly)
    */
    void draw_gouraud_lighting();

    /**
    * @brief draw draws the object with the selected method
    * @param mode {points, lines, fill, chess, flat_illum, smooth_illum}
    */
    void draw(int mode);

    /**
    * @brief calculateNormalTriangles calculates the normalized normal
    * vector of each triangle
    */
    void calculateNormalTriangles();

    /**
    * @brief calculateNormalVertices_inefficient calculates the normalized normal
    * vector of each vertex. Efficiency = O(n²)
    */
    void calculateNormalVertices_inefficient();

    /**
    * @brief calculateNormalVertices calculates the normalized normal
    * vector of each vertex. Efficiency = O(n) with dynamic programming
    */
    void calculateNormalVertices();

    /**
    * @brief setMaterial gives a material to the object (necessary for illum)
    * @param mat material data structure
    */
    void setMaterial(const _material &mat);

};

#endif // OBJECT3D_H
