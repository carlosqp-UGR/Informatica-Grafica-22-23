/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>    // pick
#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "ply_object.h"
#include "ply_revolution_object.h"
#include "funfair_attraction.h"
#include "material.h"
#include "lights.h"
#include "dashboard.h"
#include <QMouseEvent>
#include <QWheelEvent>

namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON, OBJECT_CUBE, OBJECT_CONE, OBJECT_CYLINDER, OBJECT_SPHERE,
                OBJECT_PLY, OBJECT_PLY_REVOLUTION, OBJECT_HIERARCHICAL_MODEL, OBJECT_DASHBOARD} _object;
}

class _window;

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:

    /**
     * @brief _gl_widget Constructor
     * @param Window1
     */
    _gl_widget(_window *Window1);

    /**
     * @brief clear_window
     */
    void clear_window();

    /**
     * @brief change_projection Defines the projection of the camera.
     * Can be either perspective or orthogonal projection.
     */
    void change_projection();

    /**
     * @brief change_observer Implements the view transformation
     * (transformación de vista, TV) of the camera.
     */
    void change_observer();

    /**
     * @brief draw_axis Paints X,Y and Z axis
     */
    void draw_axis();

    /**
     * @brief draw_objects Paints objects depending on the
     * state of the program's variables
     */
    void draw_objects();

    /**
     * @brief pick Implements selection of triangles with a click
     */
    void pick();

public slots:

    /**
     * @brief slotAnimation Controls the automatic movement of the
     * hierarchical object and the second light with a timer.
     */
    void slotAnimation();

protected:

    /**
     * @brief resizeGL
     * @param Width1
     * @param Height1
     */
    void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;

    /**
     * @brief paintGL Paints the scene. The steps to paint are
     * in the following order:
     * 1st clear the window
     * 2nd define the projection
     * 3rd apply the view transformation
     * 4th draw the objects
     */
    void paintGL() Q_DECL_OVERRIDE;

    /**
     * @brief initializeGL Initializes all the necessary variables
     */
    void initializeGL() Q_DECL_OVERRIDE;

    /**
     * @brief keyPressEvent
     * @param Keyevent
     */
    void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

    /**
     * @brief mousePressEvent Defines the action for a mouse press event
     * @param event Could be either right click (pick) or left click (move)
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief mouseMoveEvent Defines the action for mouse movement
     * @param event
     * @pre Mouse drag is necessary for this function to act
     */
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief mouseReleaseEvent Defines the action for a mouse release event
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief wheelEvent Defines the action for a wheel event. Creates a zoom
     * depending on the sign of the angle.
     * @param event
     */
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
    _window *Window;
    _axis Axis;
    _gl_widget_ne::_object Object;

    //[P1]
    _tetrahedron Tetrahedron;
    _cube Cube;

    //[P2]
    _cone Cone;
    _cylinder Cylinder;
    _sphere Sphere;
    _ply_object Ply_Object;
    _ply_revolution_object Ply_Revolution_Object;

    //[P3]
    _funfair_attraction Object_Hierarchical;

    // [P4]
    _dashboard Chessboard;
    _lights Lights;

    static const unsigned int num_materials = 4;
    _material Materials[num_materials];
    unsigned int idx_materials;

    /**< control state variables */
    // drawing mode
    bool Draw_point;
    bool Draw_line;
    bool Draw_fill;
    bool Draw_chess;

    // lighting
    bool Flat_lighting;
    bool Smooth_lighting;
    bool Light0;
    bool Light1;

    // textures & lighting
    bool Tex_unlit;
    bool Tex_flat;
    bool Tex_smooth;

    // animation
    bool Animation;
    bool FirstDegree;     /**< Controla el sentido del 1er grado de liberad (0=Reducir, 1=Aumentar) en la animacion */
    bool SecondDegree;    /**< Controla el sentido del 2o grado de liberad (0=Reducir, 1=Aumentar) en la animacion */
    /**< Para el 3er grado de libertad, esto no es necesario porque no tiene rango (Elegimos que smp crezca)*/

    // projection
    bool orthogonal;    /**< false:=perspectiva; true:=paralela */

    // movement and position of the observer (perspective)
    float Perspective_observer_angle_x;
    float Perspective_observer_angle_y;
    float Perspective_observer_distance;

    // movement and position of the observer (orthogonal)
    float Orthogonal_observer_angle_x;
    float Orthogonal_observer_angle_y;
    float Orthogonal_observer_distance;

    // mouse events
    // movement (calculates the difference between positions)
    int lastX;
    int lastY;
    // Para saber si se está arrastrando el ratón (rotación)
    bool mouse_drag;

    // [P5] necessary variables for pick (?)
    int Window_width;
    int Window_height;
    int Selection_position_x;
    int Selection_position_y;
};

#endif
