#include <QImageReader>
#include "tex_object3d.h"

void _tex_object3D::draw_tex() {
    // Prepara la textura para pintarla
    setTexture();
    // Al no haber iluminación, no hay que modular
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Habilitamos texturas 2d
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
        // Pasamos los vértices de los triángulos así como sus
        // coordenadas de textura
        for(unsigned int i=0;  i<Triangles.size(); ++i) {

            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][0]]);

            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][1]]);

            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][2]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][2]]);
        }
    glEnd();
    // deshabilitamos textura
    glDisable(GL_TEXTURE_2D);
}

void _tex_object3D::draw_tex_flat_lighting() {
    // Prepara la textura para pintarla
    setTexture();
    // Hay que modular debido a la iluminación
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPolygonMode(GL_FRONT, GL_FILL);
    // Habilitamos iluminación y texturas 2d
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
        // Definimos el modelo de iluminación
        glShadeModel(GL_FLAT);

        // Pasamos los vértices de los triángulos así como sus
        // coordenadas de textura y la normal del triángulo
        for(unsigned int i=0;  i<Triangles.size(); ++i) {

            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][0]]);

            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][1]]);

            glNormal3fv((GLfloat *) &NormalTriangles[i]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][2]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][2]]);
        }
    glEnd();
    // Deshabilitamos iluminación y texturas
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}

void _tex_object3D::draw_tex_gouraud_lighting() {
    // Prepara la textura para operar con ella
    setTexture();
    // Hay que modular debido a la iluminación
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPolygonMode(GL_FRONT, GL_FILL);
    // Habilitamos iluminación y texturas 2d
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
        // Definimos el modelo de iluminación
        glShadeModel(GL_SMOOTH);

        // Pasamos los vértices de los triángulos así como sus
        // coordenadas de textura y la normal del vértice
        for(unsigned int i=0;  i<Triangles.size(); ++i) {

            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][0]]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][0]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][0]]);

            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][1]]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][1]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][1]]);

            glNormal3fv((GLfloat *) &NormalVertices[Triangles[i][2]]);
            glTexCoord2fv((GLfloat *) &TexCoords[Triangles[i][2]]);
            glVertex3fv((GLfloat *) &Vertices[Triangles[i][2]]);
        }
    glEnd();
    // Deshabilitamos iluminación y texturas
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}

// Lee y carga la imagen para poder ser procesada
// (código sacado de PRADO)
void _tex_object3D::loadTexture(const char *path) {

    // code for reading an image
    QString File_name(path);
    QImageReader Reader(File_name);
    Reader.setAutoTransform(true);
    texture = Reader.read();
    if (texture.isNull()) {
        cerr << "Cannot load " << path << endl;
        exit(-1);
    } else {
        cout << "Texture loaded" << endl;
    }
    texture = texture.mirrored();
    texture = texture.convertToFormat(QImage::Format_RGB888);
}

void _tex_object3D::setTexture() {
    // code to control the application of the texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // code to pass the image to OpenGL to form a texture 2D
    glTexImage2D(GL_TEXTURE_2D,0,3,texture.width(),texture.height(),0,GL_RGB,GL_UNSIGNED_BYTE,texture.bits());
}

void _tex_object3D::calculateTexCoords() {

}
