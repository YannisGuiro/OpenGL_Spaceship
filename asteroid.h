#ifndef ASTEROID_H
#include "station.h"
#include "ship.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include <QVector3D>
#define ASTEROID_H


class Asteroid
{
public:
    Asteroid();
    ~Asteroid();

    void Initialize(float, Asteroid*, int ite, Station*, Ship*);
    void setTexture(GLuint t){astTexture = t;}

    QVector3D getPos(){return position;}
    float getRad(){return size;}


    void Update();
    void Display();


    QVector3D generateValidPosition(float delim, Asteroid*, int ite, Station*, Ship*);
    QVector3D generate(float delim);

private:
    float delim;

    const int SIZE_RANGE[2] = {5, 10};
    float size;

    float rotSpeedX, rotSpeedY;
    float rotX, rotY;
    QVector3D position; // XYZ

    GLUquadric *quad;

    GLuint astTexture; // Texture

};

#endif // ASTEROID_H
