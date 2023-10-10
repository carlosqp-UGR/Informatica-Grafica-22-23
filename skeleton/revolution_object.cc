#include "revolution_object.h"

// Algoritmo 'eficiente': forma objetos por revolución bien generados
void _revolution_object::generate_revolution_object(unsigned int n, const vector<_vertex3f> &profile) {

// (A) Analizamos el perfil: ¿0,1 o 2 tapas?

    // Como el perfil está en orden, las tapas estarán en el primer y/o último punto del perfil (si las hay)
    vector<unsigned int> tapas; // Almacena el índice de las tapas
    if(profile[0].x==0.0 && profile[0].z==0.0)
        tapas.push_back(0);

    if(profile[profile.size()-1].x==0.0 && profile[profile.size()-1].z==0.0)
        tapas.push_back(profile.size()-1);

// (B) Rotamos por revolución los puntos intermedios (se entiende por pto intermedio como aquel que no es tapa)
    unsigned int num_ptos_intermedios = profile.size()-tapas.size();

    // La constante de rotación a aplicar en cada iteración
    const float Alpha = 2.0*M_PI/(float)n;

    // Generamos los n perfiles distintos aplicando la rotación correspondiente a cada uno
    this->Vertices.clear();
    this->Vertices.resize(n*num_ptos_intermedios);
    unsigned int idx=0; // Contador necesario para indexar e insertar los puntos rotados

    // ¿Todos los objetos tienen radio? El radio, con el eje Y como eje de rotacion,
    // es el la distancia en 2d (en valor abs) de su coordenada en el eje X con el eje Y.

    for(unsigned int i=0; i<n; ++i) {
        for(unsigned int j=0; j<profile.size(); ++j) {
            if(!(profile[j].x==0 && profile[j].z==0)) {     // Evita repetir los puntos sobre el eje
                float x = cos(i*Alpha)*abs(profile[j].x);
                float y = profile[j].y; // Se mantiene cte (rotamos sobre el eje Y)
                float z = -sin(i*Alpha)*abs(profile[j].x);    // En 2d, visto desde la planta, el seno es negativo (va hacia las z negativas)
                this->Vertices[idx] = _vertex3f(x,y,z);
                idx++;
            }
        }
    }


// (C) Generamos superficie lateral (si la tiene). Para ello debe tener al menos dos ptos intermedios.
    if(num_ptos_intermedios>1) {
        // Iteraremos sobre el vector de vértices como si de una matriz se tratara
        // En cada fila guardamos un punto del perfil y sus rotados (es decir: P0 P0' P0'' ...) ->
        // hay tantas filas como puntos tenga el perfil
        // En cada columna se almacena un perfil -> hay tantas columnas como perfiles
        // A partir de ahí. formaremos cuadrados (con dos triángulos); ver guión de prácticas
        this->Triangles.clear();

        // Fórmula clase: m=num_puntos_perfil, n=num_perfiles -> num_triang = (m-1)*n*2
        this->Triangles.resize((num_ptos_intermedios-1)*n*2);
        unsigned int cont = 0;

        for(unsigned int c=0; c<n; ++c) {
            for(unsigned int r=0; r<(num_ptos_intermedios-1); ++r) {
                // Por cada vértice procesado, añadimos dos triágulos
                // Transformacion de 2d a 1d -> P[f,c] = P[ f + c*num_filas ]
                // Triángulos en sentido antihorario :  Ta=([r,c], [r,c+1], [r+1,c])
                //                                      Tb=([r+1,c], [r,c+1], [r+1,c+1])
                // Triángulos en sentido horario :      Ta=([r,c], [r+1,c], [r,c+1])
                //                                      Tb=([r+1,c], [r+1,c+1], [r,c+1])
                // Triángulos definidos en sentido antihorario (por defecto OpenGL) ~ ¿iluminación al contrario?
                // Definimos los triángulos en sentido horario para que la iluminación sea correcta
                this->Triangles[cont++] = _vertex3ui (  ( r + c*num_ptos_intermedios )    % this->Vertices.size(),
                                                        ( (r+1) + c*num_ptos_intermedios )% this->Vertices.size(),
                                                        (r + (c+1)*num_ptos_intermedios ) % this->Vertices.size() );
                this->Triangles[cont++] = _vertex3ui ( ( (r+1) + c*num_ptos_intermedios )% this->Vertices.size(),
                                                       ((r+1) + (c+1)*num_ptos_intermedios )% this->Vertices.size(),
                                                        ( r + (c+1)*num_ptos_intermedios )% this->Vertices.size() );
            }
        }
    }

// (D) Generamos tapas (si las tiene)
    for (unsigned int tp=0; tp<tapas.size(); ++tp) {
        if (tapas[tp] == 0) {
            unsigned int i = 0;
            unsigned int j = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
            for(unsigned int k=0; k<=n; ++k) {  // Recorre el vector n+1 veces (la última es para cerrar la superficie)
                // Genera los triángulos en SENTIDO ANTIHORARIO
                this->Triangles.push_back( _vertex3ui(Vertices.size(), i, j) );
                i = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
                j = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
            }
        } else {
            unsigned int i = num_ptos_intermedios-1;
            unsigned int j = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
            for(unsigned int k=0; k<=n; ++k) {  // Recorre el vector n+1 veces (la última es para cerrar la superficie)
                // Genera los triángulos en SENTIDO ANTIHORARIO
                this->Triangles.push_back( _vertex3ui(Vertices.size(), j, i) );
                i = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
                j = (i+num_ptos_intermedios)%(n*num_ptos_intermedios);
            }
        }

        // Añadimos al final las tapas del perfil. Por la forma en la que se comprueban las tapas, se guardaría primero
        // el P0 del perfil y luego el Pn (en caso de tener dos tapas).
        Vertices.push_back(profile[tapas[tp]]);
    }
}

// Algoritmo ineficiente: vértices repetidos y triángulos degenerados
void _revolution_object::generate_revolution_object_inefficient(unsigned int n, const vector<_vertex3f> &profile)
{
    // La constante de rotación a aplicar en cada iteración
    const float Alpha = 2.0*M_PI/(float)n;

    // Generamos los n perfiles distintos aplicando la rotación correspondiente a cada uno
    this->Vertices.clear();
    this->Vertices.resize(n*profile.size());
    unsigned int idx=0; // Contador necesario para indexar e insertar los puntos rotados

    // ¿Todos los objetos tienen radio? El radio, con el eje Y como eje de rotacion,
    // es el la distancia en 2d (en valor abs) de su coordenada en el eje X con el eje Y.

    for(unsigned int i=0; i<n; ++i) {
        for(unsigned int j=0; j<profile.size(); ++j) {
            float x = cos(i*Alpha)*abs(profile[j].x);
            float y = profile[j].y; // Se mantiene cte (rotamos sobre el eje Y)
            float z = -sin(i*Alpha)*abs(profile[j].x);    // En 2d, visto desde la planta, el seno es negativo (va hacia las z negativas)
            this->Vertices[idx] = _vertex3f(x,y,z);
            idx++;
        }
    }

    // Ahora es necesario generar las superficies (los triángulos)
    // Iteraremos sobre el vector de vértices como si de una matriz se tratara
    // En cada fila guardamos un punto del perfil y sus rotados (es decir: P0 P0' P0'' ...) ->
    // hay tantas filas como puntos tenga el perfil
    // En cada columna se almacena un perfil -> hay tantas columnas como perfiles
    // A partir de ahí. formaremos cuadrados (con dos triángulos); ver guión de prácticas
    this->Triangles.clear();

    // Fórmula clase: m=num_puntos_perfil, n=num_perfiles -> num_triang = (m-1)*n*2
    this->Triangles.resize((profile.size()-1)*n*2);
    unsigned int cont = 0;

    for(unsigned int c=0; c<n; ++c) {
        for(unsigned int r=0; r<(profile.size()-1); ++r) {
            // Por cada vértice procesado, añadimos dos triágulos
            // Transformacion de 2d a 1d -> P[f,c] = P[ f + c*num_filas ]
            // Triángulos en sentido antihorario :  Ta=([r,c], [r,c+1], [r+1,c])
            //                                      Tb=([r+1,c], [r,c+1], [r+1,c+1])
            // Triángulos en sentido horario :      Ta=([r,c], [r+1,c], [r,c+1])
            //                                      Tb=([r+1,c], [r+1,c+1], [r,c+1])
            // Triángulos definidos en sentido antihorario (por defecto OpenGL) ~ ¿iluminación al contrario?
            // Definimos los triángulos en sentido horario para que la iluminación sea correcta
            this->Triangles[cont++] = _vertex3ui ( ( r + c*profile.size() )    % this->Vertices.size(),
                                                   ( (r+1) + c*profile.size() )% this->Vertices.size(),
                                                    (r + (c+1)*profile.size() ) % this->Vertices.size());
            this->Triangles[cont++] = _vertex3ui ( ((r+1) + c*profile.size() )% this->Vertices.size(),
                                                   ( (r+1) + (c+1)*profile.size() )% this->Vertices.size(),
                                                   (r + (c+1)*profile.size() )% this->Vertices.size() );
        }
    }
}
