#ifndef _TEX_OBJECT3D_H
#define _TEX_OBJECT3D_H

#include <QImage>
#include "object3d.h"

/**
 * @brief The _tex_object3D class
 * Clase hija de object3D, añade coordenadas de textura (puesto que no todos los
 * objetos tienen textura). Tiene como atributos adicionales:
 * - Imagen de textura
 * - Coordenadas de textura de cada vértice
 */
class _tex_object3D: public _object3D {
public:
    QImage texture;                 /**< Processed and normalized texture image */
    vector<_vertex2f> TexCoords;    /**< Texture coordinates for each vertex */

    /**
     * @brief loadTexture opens, reads and processes the texture
     * @param path to open and load the image
     */
    void loadTexture(const char *path);

    /**
     * @brief setTexture sets the texture to work with
     */
    void setTexture();

    /**
     * @brief draw_tex draws the object with unlit texture
     */
    void draw_tex();

    /**
     * @brief draw_tex_flat_lighting draws the object with
     * texture and flat lighting
     */
    void draw_tex_flat_lighting();

    /**
     * @brief draw_tex_gouraud_lighting draws the object with
     * texture and smooth lighting
     */
    void draw_tex_gouraud_lighting();

    /**
     * @brief calculateTexCoords
     * Pure virtual method: it must be overriden by every descendent
     * class because each object has a unique way of mapping its
     * texture.
     */
    virtual void calculateTexCoords()=0;
};

#endif // _TEX_OBJECT3D_H
