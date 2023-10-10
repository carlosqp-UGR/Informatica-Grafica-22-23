// Carlos Quesada Pérez
/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    // Primitiva GL_LINES: cada dos puntos pinta la línea
    glBegin(GL_LINES);

        // Para pintar las líneas, se pintan las aristas de cada triángulo
        // que forma el objeto. Para ello se le pasan los vertices del
        // triángulo dos a dos (problema, las aristas compartidas se pintan
        // mas de una vez, no es óptimo ¿?).
        // Orden en el que se pintan las aristas: AB, AC, BC
        for(unsigned int t=0; t<Triangles.size(); ++t) {
            for(unsigned int i=0; i<2; ++i) {
                unsigned int idx1 = Triangles[t][i];
                for(unsigned int j=i+1; j<3; ++j) {
                    unsigned int idx2 = Triangles[t][j];
                    glVertex3fv((GLfloat *) &Vertices[idx1]);
                    glVertex3fv((GLfloat *) &Vertices[idx2]);
                }
            }
        }

    glEnd();
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    // docs.gl: glPolygonMode - select a polygon rasterization mode
    glPolygonMode(GL_FRONT, GL_FILL);

    // Primitiva GL_TRIANGLES: cada tres puntos pinta un triángulo (su relleno)
    glBegin(GL_TRIANGLES);


        // Para pintar las superficies basta con la primitiva GL_TRIANGLES y con
        // pasar los vértices de cada triángulo de tres en tres.
        for(unsigned int t=0; t<Triangles.size(); ++t) {
            if((int)t==pick_triangle) glColor3fv((GLfloat *) &YEllOW);
            else glColor3fv((GLfloat *) &BLUE);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][2]]);
        }

    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    // Preguntar por que usar ese modo, sin glPolygonMode tambien funciona.
    glPolygonMode(GL_FRONT, GL_FILL);

    // Primitiva GL_TRIANGLES: cada tres puntos pinta un triángulo (su relleno)
    glBegin(GL_TRIANGLES);

        // Para pintar las superficies basta con la primitiva GL_TRIANGLES y con
        // pasar los vértices de cada triángulo de tres en tres.
        for(unsigned int t=0; t<Triangles.size(); ++t) {
            if(t%2==0) glColor3fv((GLfloat *) &RED);
            else glColor3fv((GLfloat *) &GREEN);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][2]]);
        }

    glEnd();

}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
void _object3D::draw_selection() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLES);

        float Red, Green, Blue;
        for(unsigned int t=0; t<Triangles.size(); ++t) {
            // Convertimos el índice de cada triángulo en un color único
            Red = (t & 0x00FF0000) >> 16;
            Green = (t & 0x0000FF00) >> 8;
            Blue = (t & 0x000000FF);

            glColor3f(Red/255.0, Green/255.0, Blue/255.0);

            glVertex3fv((GLfloat *) &Vertices[Triangles[t][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[t][2]]);
        }

    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// Para pintar fácilmente los objetos jerárquicos y no repetir código.
void _object3D::draw(int mode) {
    switch (mode) {
    case 0: this->draw_point(); break;
    case 1: this->draw_line(); break;
    case 2: this->draw_fill(); break;
    case 3: this->draw_chess(); break;
    case 4: this->draw_flat_lighting(); break;
    case 5: this->draw_gouraud_lighting(); break;
    case 6: this->draw_selection(); break;
    default: break;
    }
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// Calcula las normales de los triángulos (haciendo uso de las funciones que pro-
// porciona <vertex.h>), las normaliza y las guarda en NormalTriangles.
void _object3D::calculateNormalTriangles() {

    // Redimensionar NormalTriangles
    this->NormalTriangles.clear();
    this->NormalTriangles.resize(this->Triangles.size());

    // Variables auxiliares
    _vertex3f v0v1;
    _vertex3f v0v2;

    // Calcular las normales y normalizarlas
    for(unsigned int i=0; i<Triangles.size(); ++i) {
        v0v1 = Vertices[Triangles[i][1]] - Vertices[Triangles[i][0]];       // v1-v0
        v0v2 = Vertices[Triangles[i][2]] - Vertices[Triangles[i][0]];       // v2-v0
        NormalTriangles[i] = (v0v1.cross_product(v0v2)).normalize();        // v0v1 X v0v2  (normalizado)
    }
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// Calcula las normales de los vértices (haciendo uso de las funciones que pro-
// porciona <vertex.h>). Se basa en las normales previamente calculadas de los
// triángulos, realizando la media aritmética de las normales de todas las caras
// (triángulos) que contienen al vértice. Versión ineficiente de fuerza bruta O(n^2)
void _object3D::calculateNormalVertices_inefficient() {

    // Redimensionar el vector
    this->NormalVertices.clear();
    this->NormalVertices.resize(this->Vertices.size());

    // Almacenan los datos necesarios para la media aritmética
    _vertex3f sumatorio;
    unsigned int n;

    // Recorremos los vértices
    for (unsigned int i=0; i<Vertices.size(); ++i) {
        // reiniciamos variables
        sumatorio = _vertex3f(0,0,0);
        n = 0;

        // Recorremos los triángulos en busca del vertice de posición i
        for(unsigned int j=0; j<Triangles.size(); ++j) {
            // Si el triángulo contiene al vértice, le sumamos su normal
            if( (Triangles[j][0]==i) || (Triangles[j][1]==i) || (Triangles[j][2]==i) ) {
                sumatorio += NormalTriangles[i];
                n++;
            }
        }

        // Para evitar el error en la division
        if(n>0) {
            // La normal del vértice es su media aritmética NORMALIZADA
            NormalVertices[i] = (sumatorio/(float)n).normalize();
        }
    }   // O(n^2)
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// Calcula las normales de los vértices (haciendo uso de las funciones que pro-
// porciona <vertex.h>). Se basa en las normales previamente calculadas de los
// triángulos, realizando la media aritmética de las normales de todas las caras
// (triángulos) que contienen al vértice. Versión eficiente Programación Dinámica O(n)
void _object3D::calculateNormalVertices() {
    // Algoritmo de Programación Dinámica,  más pesado en memoria pero eficiente en cómputo
    // Creamos un vector del tamaño del número de vértices, que almacenará parejas de valores
    // {_vector3f, unsigned int}. La idea es, almacenar en la misma posición que ocupe el vértice
    // en el vector de vértices, ir almacenando la suma de las normales de los triángulos que lo
    // contienen (así como el número de triángulos que lo contienen). De esta forma, con esta
    // "memoria" auxiliar, tras recorrer el vector de triángulos e ir rellenándola, obtendremos
    // los datos suficientes para poder calcular la normal del vértice tras sólo una barrida O(n).

    // Constructor que inicializa la estructura al tamaño vertices.size() y valor por defecto ({0,0,0},0)
    vector<pair<_vertex3f, unsigned int>> memory (Vertices.size(), pair<_vertex3f,unsigned int>(_vertex3f(0,0,0), 0));

    // Redimensionamos NormalVertices
    this->NormalVertices.clear();
    this->NormalVertices.resize(this->Vertices.size());

    // Recorremos el vector de triángulos
    for(unsigned int i=0; i<Triangles.size(); ++i) {
        // Guardamos los índices de los vértices que componen el triángulo i
        unsigned idx0, idx1, idx2;
        idx0 = Triangles[i][0];
        idx1 = Triangles[i][1];
        idx2 = Triangles[i][2];

        // Para cada vértice, actualizamos sus variables en la memoria, en su posición real (idx(n))
        memory[idx0].first += NormalTriangles[i];   memory[idx0].second++;
        memory[idx1].first += NormalTriangles[i];   memory[idx1].second++;
        memory[idx2].first += NormalTriangles[i];   memory[idx2].second++;
    }

    // Ya tenemos la memoria rellena, ahora calculamos la normal como la media y despues la normalizamos
    for(unsigned int i=0; i<Vertices.size(); ++i) {
        // Evita el error de la división por 0
        if(memory[i].second>0) {
            // Calcula la media aritmética
            NormalVertices[i] = (memory[i].first/(float)memory[i].second).normalize();
        }
    }

}   // Se borra la memoria dinámica

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_flat_lighting() {
    glPolygonMode(GL_FRONT, GL_FILL);
    // Para resolver el problema de las normales tras las transformaciones,
    // habilitamos esta opción que normaliza las normales tras aplicar transformaciones
    // docs.gl: GL_RESCALE_NORMAL ...normal vectors are scaled after transformation and
    // before lighting by a factor computed from the modelview matrix...
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);
        glShadeModel(GL_FLAT);

        // Para pintar GL_FLAT pasamos la misma normal (la del triángulo) tres veces
        for(unsigned int i=0; i<Triangles.size(); ++i) {
            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][0]]);

            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][1]]);

            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][2]]);
        }

    glEnd();
    glDisable(GL_LIGHTING);
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_gouraud_lighting() {
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);
        glShadeModel(GL_SMOOTH);

        // Para pintar GL_SMOOTH pasamos la normal de cada vértice
        for(unsigned int i=0; i<Triangles.size(); ++i) {
            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][0]]);

            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][1]]);

            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][2]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][2]]);
        }

    glEnd();
    glDisable(GL_LIGHTING);

}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::setMaterial(const _material &mat) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, (const GLfloat*) &mat.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (const GLfloat*) &mat.specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, (const GLfloat*) &mat.ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, (const GLfloat*) &mat.shine);
}
