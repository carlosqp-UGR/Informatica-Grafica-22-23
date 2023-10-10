#include "material.h"

_material::_material(const _vertex4f &d, const _vertex4f &sp,const _vertex4f &a, float sh) {
    setDiffuseComponent(d);
    setSpecularComponent(sp);
    setAmbientComponent(a);
    setShineComponent(sh);
}
