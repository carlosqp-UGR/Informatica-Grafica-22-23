/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef BASIC_OBJECT3D_H
#define BASIC_OBJECT3D_H

#include <vector>
#include <GL/gl.h>
#include "colors.h"
#include "vertex.h"


/**
 * @brief The _basic_object3D class
 * Basic class that only stores vertices
 */
class _basic_object3D
{
  public:
  vector<_vertex3f> Vertices;

  /**
   * @brief draw_point Paints the object's vertices
   */
  void draw_point();
};

#endif
