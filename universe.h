#ifndef UNIVERSE_H
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include "asteroid.h"
#define UNIVERSE_H


class Universe
{
public:
    Universe(Asteroid*, int, Station*, Ship*);
    ~Universe();
    // Methode d'affichage
    void Update();
    void Display(QVector3D) const;

private:
    GLUquadric *quad;
    GLuint sp_texture;

    Asteroid *asteroids;
    int nb_asteroids;
    float ast_delim = 400; // Périmètre de spawn des astéroîdes.

    Station *station;
};

#endif // UNIVERSE_H
