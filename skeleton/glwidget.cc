/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;

/*****************************************************************************/
// Constructor
_gl_widget::_gl_widget(_window *Window1):Window(Window1), Chessboard(8,2.5) {
    setMinimumSize(300, 300);
    setFocusPolicy(Qt::StrongFocus);
}

/*****************************************************************************/
//Evento tecla pulsada
void _gl_widget::keyPressEvent(QKeyEvent *Keyevent) {
    switch(Keyevent->key()){
        case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
        case Qt::Key_2:Object=OBJECT_CUBE;break;
        case Qt::Key_3:Object=OBJECT_CONE;break;
        case Qt::Key_4:Object=OBJECT_CYLINDER;break;
        case Qt::Key_5:Object=OBJECT_SPHERE;break;
        case Qt::Key_6:Object=OBJECT_PLY;break;
        case Qt::Key_7:Object=OBJECT_HIERARCHICAL_MODEL;break;
        case Qt::Key_8:Object=OBJECT_DASHBOARD; break;
        case Qt::Key_9:Object=OBJECT_PLY_REVOLUTION;break;


        case Qt::Key_P:Draw_point=!Draw_point;break;
        case Qt::Key_L:Draw_line=!Draw_line;break;
        case Qt::Key_F:Draw_fill=!Draw_fill;break;    // fill mode
        case Qt::Key_F1:Draw_fill=!Draw_fill;break;   // ¿solid mode?
        case Qt::Key_F2:Draw_chess=!Draw_chess;break;
        case Qt::Key_F3:Flat_lighting=!Flat_lighting; break;
        case Qt::Key_F4:Smooth_lighting=!Smooth_lighting; break;
        case Qt::Key_F5:Tex_unlit=!Tex_unlit; break;
        case Qt::Key_F6:Tex_flat=!Tex_flat; break;
        case Qt::Key_F7:Tex_smooth=!Tex_smooth; break;

        case Qt::Key_J:Light0=!Light0; break;
        case Qt::Key_K:Light1=!Light1; break;

        case Qt::Key_M:idx_materials = (idx_materials+1)%num_materials; break;
        case Qt::Key_A:Animation=!Animation;break;

        case Qt::Key_Left:
            if(orthogonal) Orthogonal_observer_angle_y-=ANGLE_STEP;
            else  Perspective_observer_angle_y-=ANGLE_STEP;
            break;
        case Qt::Key_Right:
            if(orthogonal) Orthogonal_observer_angle_y+=ANGLE_STEP;
            else  Perspective_observer_angle_y+=ANGLE_STEP;
            break;
        case Qt::Key_Up:
            if(orthogonal) Orthogonal_observer_angle_x-=ANGLE_STEP;
            else  Perspective_observer_angle_x-=ANGLE_STEP;
            break;
        case Qt::Key_Down:
            if(orthogonal) Orthogonal_observer_angle_x+=ANGLE_STEP;
            else  Perspective_observer_angle_x+=ANGLE_STEP;
            break;
        case Qt::Key_PageUp:
        case Qt::Key_Minus:
            if(orthogonal) Orthogonal_observer_distance*=1.2;
            else Perspective_observer_distance*=1.2;
            break;
        case Qt::Key_PageDown:
        case Qt::Key_Plus:
            if(orthogonal) Orthogonal_observer_distance/=1.2;
            else Perspective_observer_distance/=1.2;
            break;

        // 1st degree of freedom
        case Qt::Key_Q:Object_Hierarchical.increaseSigma(); break;
        case Qt::Key_W:Object_Hierarchical.decreaseSigma(); break;
        case Qt::Key_E:Object_Hierarchical.increaseSigmaVelocity(); break;
        case Qt::Key_R:Object_Hierarchical.decreaseSigmaVelocity(); break;

        // 2nd degree of freedom
        case Qt::Key_S:Object_Hierarchical.increaseAlpha(); break;
        case Qt::Key_D:Object_Hierarchical.decreaseAlpha(); break;
        case Qt::Key_T:Object_Hierarchical.increaseAlphaVelocity(); break;
        case Qt::Key_Y:Object_Hierarchical.decreaseAlphaVelocity(); break;

        // 3rd degree of freedom
        case Qt::Key_Z:Object_Hierarchical.increaseBeta(); break;
        case Qt::Key_X:Object_Hierarchical.decreaseBeta(); break;
        case Qt::Key_U:Object_Hierarchical.increaseBetaVelocity(); break;
        case Qt::Key_I:Object_Hierarchical.decreaseBetaVelocity(); break;

        case Qt::Key_C:orthogonal=false; break;
        case Qt::Key_V:orthogonal=true; break;
    }

    update();
}

/*****************************************************************************/
//Limpiar ventana
void _gl_widget::clear_window() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

/*****************************************************************************/
// Funcion para definir la transformación de proyeccion
void _gl_widget::change_projection() {
    // Establecemos el modo de la matriz a proyección.
    glMatrixMode(GL_PROJECTION);
    // Carga la matriz de identidad
    glLoadIdentity();

    // Explicado en teoría (ver apuntes): para NO DEFORMAR la vista al cambiar el tamaño
    // de la ventana , debemos cambiar/igualar la TA(Tasa de Aspecto) = width/height de
    // la ventana de dispositivo a la TA del tamaño de la ventana de vista del PD de proyección.
    // (tasa de aspecto de ventana de dispositivo = tasa de aspecto ventana de vista)
    // TA(dispositvo) = (this->width)/(this->height)
    // TA(vista) = X/Y = 1/1 cuadrado
    // Para igualarlo, hay dos opciones (ambas opciones son válidas):
    // Si mantenemos Y cte: width/height = X/1 -> X*=width/height
    // Si mantenemos X cte: width/height = 1/Y -> Y*=height/width

    if(!orthogonal) { // perspectiva
        // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
        // Front_plane>0  Back_plane>PlanoDelantero)
        glFrustum(X_MIN*((float)this->width()/(float)this->height()),
                X_MAX*((float)this->width()/(float)this->height()),
                Y_MIN,
                Y_MAX,
                FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    } else {
        // paralela -> Para hacer zoom escalamos el tamaño de la ventana (Observer_distance), puesto que no importa
        // la profundidad del objeto (se ve siempre del mismo tamaño, proyectores paralelos). De esta forma:
        // - Si la ventana es más pequeña, veremos con más detalle (AMPLIAR)
        // - Si la ventana es más grande, veremos con menos detalle (ALEJAR)
        glOrtho(5*X_MIN*Orthogonal_observer_distance,5*X_MAX*Orthogonal_observer_distance,
              5*Y_MIN*Orthogonal_observer_distance*((float)this->height()/(float)this->width()),
              5*Y_MAX*Orthogonal_observer_distance*((float)this->height()/(float)this->width()),
              FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    }
}



/*****************************************************************************/
// Funcion para definir la transformación de vista (posicionar la camara)
void _gl_widget::change_observer() {
    // posicion del observador
    glMatrixMode(GL_MODELVIEW); // establecemos el modo de la matriz a model view (cambiar camara)
    glLoadIdentity(); // Cargamos la matriz identidad

    // Cada cámara tiene una transformación diferente
    if (orthogonal) {
        glTranslatef(0,0,-Orthogonal_observer_distance); // Modificamos los valores de la cámara
        glRotatef(Orthogonal_observer_angle_x,1,0,0);
        glRotatef(Orthogonal_observer_angle_y,0,1,0);
    } else {
        glTranslatef(0,0,-Perspective_observer_distance); // Modificamos los valores de la cámara
        glRotatef(Perspective_observer_angle_x,1,0,0);
        glRotatef(Perspective_observer_angle_y,0,1,0);
    }
}


/*****************************************************************************/
//Funcion que dibuja los objetos (pinta la escena 3D)
void _gl_widget::draw_objects() {
    Axis.draw_line();

    // Dibujar punto
    if (Draw_point){
        glPointSize(5);
        glColor3fv((GLfloat *) &BLACK);
        switch (Object){
            case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
            case OBJECT_CUBE: Cube.draw_point();break;
            case OBJECT_CONE: Cone.draw_point(); break;
            case OBJECT_CYLINDER: Cylinder.draw_point(); break;
            case OBJECT_SPHERE: Sphere.draw_point(); break;
            case OBJECT_PLY: Ply_Object.draw_point(); break;
            case OBJECT_PLY_REVOLUTION: Ply_Revolution_Object.draw_point(); break;
            case OBJECT_HIERARCHICAL_MODEL: Object_Hierarchical.draw(0); break;
            case OBJECT_DASHBOARD: Chessboard.draw(0); break;
            default:break;
        }
    }

    // Dibujar linea
    if (Draw_line) {
        glLineWidth(3);
        glColor3fv((GLfloat *) &MAGENTA);
        switch (Object){
            case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
            case OBJECT_CUBE: Cube.draw_line();break;
            case OBJECT_CONE: Cone.draw_line(); break;
            case OBJECT_CYLINDER: Cylinder.draw_line(); break;
            case OBJECT_SPHERE: Sphere.draw_line(); break;
            case OBJECT_PLY: Ply_Object.draw_line(); break;
            case OBJECT_PLY_REVOLUTION: Ply_Revolution_Object.draw_line(); break;
            case OBJECT_HIERARCHICAL_MODEL: Object_Hierarchical.draw(1); break;
            case OBJECT_DASHBOARD: Chessboard.draw(1); break;
            default:break;
        }
    }

    // Dibujar superficie
    if (Draw_fill){
        switch (Object){
            case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
            case OBJECT_CUBE: Cube.draw_fill();break;
            case OBJECT_CONE: Cone.draw_fill(); break;
            case OBJECT_CYLINDER: Cylinder.draw_fill(); break;
            case OBJECT_SPHERE: Sphere.draw_fill(); break;
            case OBJECT_PLY: Ply_Object.draw_fill(); break;
            case OBJECT_PLY_REVOLUTION: Ply_Revolution_Object.draw_fill(); break;
            case OBJECT_HIERARCHICAL_MODEL: Object_Hierarchical.draw(2); break;
            case OBJECT_DASHBOARD: Chessboard.draw(2); break;
            default:break;
        }
    }

    // Dibujar ajedrez
    if (Draw_chess){
        switch (Object){
            case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
            case OBJECT_CUBE: Cube.draw_chess();break;
            case OBJECT_CONE: Cone.draw_chess(); break;
            case OBJECT_CYLINDER: Cylinder.draw_chess(); break;
            case OBJECT_SPHERE: Sphere.draw_chess(); break;
            case OBJECT_PLY: Ply_Object.draw_chess(); break;
            case OBJECT_PLY_REVOLUTION: Ply_Revolution_Object.draw_chess(); break;
            case OBJECT_HIERARCHICAL_MODEL: Object_Hierarchical.draw(3); break;
            case OBJECT_DASHBOARD: Chessboard.draw(3); break;
            default:break;
        }
    }

    // Activar/desactivar las luces
    if(Light0)    Lights.enableLight0();
    else          Lights.disableLight0();

    if (Light1)   Lights.enableLight1();
    else          Lights.disableLight1();

    // Dibujar iluminación plana (importante definir el material)
    if(Flat_lighting) {
      switch (Object){
          case OBJECT_TETRAHEDRON:
              Tetrahedron.setMaterial(Materials[idx_materials]);
              Tetrahedron.draw_flat_lighting();
              break;
          case OBJECT_CUBE:
              Cube.setMaterial(Materials[idx_materials]);
              Cube.draw_flat_lighting();
              break;
          case OBJECT_CONE:
              Cone.setMaterial(Materials[idx_materials]);
              Cone.draw_flat_lighting();
              break;
          case OBJECT_CYLINDER:
              Cylinder.setMaterial(Materials[idx_materials]);
              Cylinder.draw_flat_lighting();
              break;
          case OBJECT_SPHERE:
              Sphere.setMaterial(Materials[idx_materials]);
              Sphere.draw_flat_lighting();
              break;
          case OBJECT_PLY:
              Ply_Object.setMaterial(Materials[idx_materials]);
              Ply_Object.draw_flat_lighting();
              break;
          case OBJECT_PLY_REVOLUTION:
              Ply_Revolution_Object.setMaterial(Materials[idx_materials]);
              Ply_Revolution_Object.draw_flat_lighting();
              break;
          case OBJECT_HIERARCHICAL_MODEL:
              Object_Hierarchical.setMaterial(Materials[idx_materials]);
              Object_Hierarchical.draw(4);
              break;
          case OBJECT_DASHBOARD:
              Chessboard.setMaterial(Materials[idx_materials]);
              Chessboard.draw(4);
              break;
          default:break;
      }
    }

    // Dibujar iluminación suave (importante definir el material)
    if(Smooth_lighting) {
        switch (Object){
            case OBJECT_TETRAHEDRON:
                Tetrahedron.setMaterial(Materials[idx_materials]);
                Tetrahedron.draw_gouraud_lighting();
                break;
            case OBJECT_CUBE:
                Cube.setMaterial(Materials[idx_materials]);
                Cube.draw_gouraud_lighting();
                break;
            case OBJECT_CONE:
                Cone.setMaterial(Materials[idx_materials]);
                Cone.draw_gouraud_lighting();
                break;
            case OBJECT_CYLINDER:
                Cylinder.setMaterial(Materials[idx_materials]);
                Cylinder.draw_gouraud_lighting();
                break;
            case OBJECT_SPHERE:
                Sphere.setMaterial(Materials[idx_materials]);
                Sphere.draw_gouraud_lighting();
                break;
            case OBJECT_PLY:
                Ply_Object.setMaterial(Materials[idx_materials]);
                Ply_Object.draw_gouraud_lighting();
                break;
            case OBJECT_PLY_REVOLUTION:
                Ply_Revolution_Object.setMaterial(Materials[idx_materials]);
                Ply_Revolution_Object.draw_gouraud_lighting();
                break;
            case OBJECT_HIERARCHICAL_MODEL:
                Object_Hierarchical.setMaterial(Materials[idx_materials]);
                Object_Hierarchical.draw(5);
                break;
            case OBJECT_DASHBOARD:
                Chessboard.setMaterial(Materials[idx_materials]);
                Chessboard.draw(5);
                break;
            default:break;
        }
    }

    if(Tex_unlit && Object==OBJECT_DASHBOARD) {
        Chessboard.draw_tex();
    }

    if(Tex_flat && Object==OBJECT_DASHBOARD) {
        Chessboard.setMaterial(Materials[idx_materials]);
        Chessboard.draw_tex_flat_lighting();
    }

    if(Tex_smooth && Object==OBJECT_DASHBOARD) {
        Chessboard.setMaterial(Materials[idx_materials]);
        Chessboard.draw_tex_gouraud_lighting();
    }

    update();
}

/*****************************************************************************/
// Evento de dibujado
void _gl_widget::paintGL() {
    // Limpia el color y la profundidad de la ventana.
    // El estado del widget se mantiene por ese debemos
    // limpiar antes, si no estaríamos pintando encima.
    clear_window();
    change_projection();
    change_observer();
    draw_objects();
}

/*****************************************************************************/
//Evento de cambio de tamaño de la ventana
void _gl_widget::resizeGL(int Width1, int Height1) {
  glViewport(0,0,Width1,Height1);
}

/*****************************************************************************/
// Inicialización de OpenGL
void _gl_widget::initializeGL() {
    const GLubyte* strm;

    strm = glGetString(GL_VENDOR);
    std::cerr << "Vendor: " << strm << "\n";
    strm = glGetString(GL_RENDERER);
    std::cerr << "Renderer: " << strm << "\n";
    strm = glGetString(GL_VERSION);
    std::cerr << "OpenGL Version: " << strm << "\n";

    if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

    strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cerr << "GLSL Version: " << strm << "\n";

    int Max_texture_size=0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
    std::cerr << "Max texture size: " << Max_texture_size << "\n";

    glClearColor(1.0,1.0,1.0,1.0); // Limpiar la ventana a blanco
    glEnable(GL_DEPTH_TEST);; // Test de profundidad

    // Modificación de variables de nuestro widget. Las variables está definidas en la cabecera (.h)
    // Establecemos los tipos de primitivas y la posición de la cámara inicial.
    Perspective_observer_angle_x=0;
    Perspective_observer_angle_y=0;
    Perspective_observer_distance=DEFAULT_DISTANCE;

    Orthogonal_observer_angle_x=0;
    Orthogonal_observer_angle_y=0;
    Orthogonal_observer_distance=DEFAULT_DISTANCE;

    Draw_point=false;
    Draw_line=true;
    Draw_fill=false;
    Draw_chess=false;
    Flat_lighting = false;
    Smooth_lighting = false;
    Tex_unlit = false;
    Tex_flat = false;
    Tex_smooth = false;

    // Inicializamos las luces
    Lights = _lights();
    Light0 = false;
    Light1 = false;

    Animation = false;
    FirstDegree = true;
    SecondDegree = true;

    // Definimos los distintos materiales; para ver coeficientes de distintos materiales, ver este enlace
    // http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
    idx_materials = 0;
    // Default
    Materials[0] = _material(_vertex4f(0.8, 0.8, 0.8, 1.0),
                           _vertex4f(0.0, 0.0, 0.0, 1.0),
                           _vertex4f(0.2, 0.2, 0.2, 1.0),
                           0.0f);
    //Polished bronze
    Materials[1] = _material(_vertex4f(0.4f, 0.2368f, 0.1036f, 1.0f),             // diffuse
                           _vertex4f(0.774597f, 0.458561f, 0.200621f, 1.0f),      // specular
                           _vertex4f(0.25f, 0.148f, 0.06475f, 1.0f),              // ambient
                           76.8f);                                                // shininess
    //Green plastic
    Materials[2] = _material(_vertex4f(0.1f,0.35f,0.1f,1.0f),                     // diffuse
                           _vertex4f(0.45f,0.55f,0.45f,1.0f),                     // specular
                           _vertex4f(0.0f,0.0f,0.0f,1.0f),                        // ambient
                           32.0f);                                                // shininess
    // Red Rubber
    Materials[3] = _material(_vertex4f(0.5f, 0.4f, 0.4f, 1.0f),                       // diffuse
                           _vertex4f(0.7f, 0.04f, 0.04f, 1.0f),                     // specular
                           _vertex4f(0.05f, 0.0f, 0.0f, 1.0f),                      // ambient
                           10.0f);                                                  // shininess

    // [P5]
    orthogonal = false; // perspectiva

    // mouse events
    lastX = 0;
    lastY = 0;
    mouse_drag = false;

    // pick
    // Dentro de un contexto válido de OpenGL inicializar GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) {
      std::cerr << "Error initializing 'glew.h'\n";
      exit(-1);
    }

    Window_width = this->width();
    Window_height = this->height();
    Selection_position_x = 0;
    Selection_position_y = 0;
}

/*****************************************************************************/
// Slot para animación
void _gl_widget::slotAnimation() {
    if (Animation) {
        // Rotation of the 2nd light aroung the Y axis
        Lights.rotateLight1();

        // 1st Degree of Freedom
        if(FirstDegree) {
            FirstDegree = Object_Hierarchical.increaseSigma();
        } else {
            FirstDegree = !(Object_Hierarchical).decreaseSigma();
        }
        // 2nd Degree of Freedom
        if(SecondDegree) {
            SecondDegree = Object_Hierarchical.increaseAlpha();
        } else {
            SecondDegree = !(Object_Hierarchical.decreaseAlpha());
        }
        // 3rd Degree of Freedom
        Object_Hierarchical.increaseBeta();

        // update window
        update();
    }
}

/*****************************************************************************/
// Para seleccionar -> click derecho (pick)
// Para arrastrar y mover la cámara -> mantener click izquierdo y arrastrar el ratón
void _gl_widget::mousePressEvent(QMouseEvent *event){
    // Arrastrar (mover cámara)
    if (event->buttons() == Qt::LeftButton) {
        lastX = event->x();
        lastY = event->y();
        mouse_drag = true;
    } else if (event->buttons() == Qt::RightButton) {
        // Actualizamos las variables necesarias para el pick
        Window_width = this->width();
        Window_height = this->height();
        Selection_position_x = event->x();
        Selection_position_y = event->y();
        this->pick();
    }
    update();
}

/*****************************************************************************/
// Mientras tengamos pulsado el click izquierdo y arrastremos
void _gl_widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()==Qt::LeftButton && mouse_drag) {
        if(orthogonal) {
            Orthogonal_observer_angle_y += ((event->x()-lastX)/360.0);  // Rotacion eje Y
            Orthogonal_observer_angle_x += ((event->y()-lastY)/360.0);  // Rotacion eje X
        } else {
            Perspective_observer_angle_y += ((event->x()-lastX)/360.0); // Rotacion eje Y
            Perspective_observer_angle_x += ((event->y()-lastY)/360.0); // Rotacion eje X
        }
    }
    update();
}

/*****************************************************************************/
// Cuando terminemos de arrastrar, soltamos click izquierdo
void _gl_widget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton) mouse_drag = false;
    update();
}

/*****************************************************************************/
// https://doc.qt.io/qt-6/qwheelevent.html#angleDelta
// Returns the relative amount that the wheel was rotated, in eighths of a degree.
// A positive value indicates that the wheel was rotated forwards away from the user;
// a negative value indicates that the wheel was rotated backwards toward the user.
// angleDelta().y() provides the angle through which the common vertical mouse wheel
// was rotated since the previous event.
void _gl_widget::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y()>0) {  // Aumentar
        if(orthogonal) Orthogonal_observer_distance/=1.2;
        else Perspective_observer_distance/=1.2;
    } else {                // Alejar
        if(orthogonal) Orthogonal_observer_distance*=1.2;
        else Perspective_observer_distance*=1.2;
    }
    update();
}

/*****************************************************************************/
// Skeleton for pick fuction using glDeleteFramebuffers
//
// Domingo Martín Perandrés
// GPL
//
// Window_width and Window_height are the widht and height of the device window
// Selection_position_x and Selection_position_y are the coordinates of the mouse
// Skeleton for pick fuction using glDeleteFramebuffers
//
// Domingo Martín Perandrés
// GPL
//
// Window_width and Window_height are the widht and height of the device window
// Selection_position_x and Selection_position_y are the coordinates of the mouse
void _gl_widget::pick() {
/*
    makeCurrent();

    // Frame Buffer Object to do the off-screen rendering
    GLuint FBO;
    glGenFramebuffers(1,&FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);

    // Texture for drawing
    GLuint Color_texture;
    glGenTextures(1,&Color_texture);
    glBindTexture(GL_TEXTURE_2D,Color_texture);
    // RGBA8
    glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, Window_width,Window_height);
    // this implies that there is not mip mapping
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // Texure for computing the depth
    GLuint Depth_texture;
    glGenTextures(1,&Depth_texture);
    glBindTexture(GL_TEXTURE_2D,Depth_texture);
    // Float
    glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, Window_width,Window_height);

    // Attatchment of the textures to the FBO
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

    // OpenGL will draw to these buffers (only one in this case)
    static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1,Draw_buffers);

    // dibujar escena para seleccion

    // get the pixel
    int Color;
    glReadBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(Selection_position_x,Selection_position_y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&Color);

    // convertir de RGB a identificador

    // actualizar el identificador de la parte seleccionada en el objeto

    glDeleteTextures(1,&Color_texture);
    glDeleteTextures(1,&Depth_texture);
    glDeleteFramebuffers(1,&FBO);
    // the normal framebuffer takes the control of drawing
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());
*/
}
