#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <vertex.h>

/**
 * @brief The _material class
 * Data structure to store the values of a material
 * http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
 */
class _material
{
public:
    _vertex4f diffuse;
    _vertex4f specular;
    _vertex4f ambient;
    float shine;

    _material(const _vertex4f &d=_vertex4f(0,0,0,1),const _vertex4f &sp=_vertex4f(0,0,0,1),const _vertex4f &a=_vertex4f(0,0,0,1), float sh=0);
    inline void setDiffuseComponent(const _vertex4f &d) { this->diffuse = d; }
    inline void setSpecularComponent(const _vertex4f &sp) { this->specular = sp; }
    inline void setAmbientComponent(const _vertex4f &a) { this->ambient = a; }
    inline void setShineComponent(float sh) { this->shine=sh; }
};

#endif // _MATERIAL_H
