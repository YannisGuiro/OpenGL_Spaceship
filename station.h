#ifndef STATION_H
#include <QElapsedTimer>
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QVector3D>
#include <QImage>
#define STATION_H


class Station
{
public:
    Station();
    ~Station();

    float getHitboxSize() {return hbSize;}
    QVector3D getHitBoxPos() {return QVector3D(position[0], position[1]+5, position[2]);}
    void Update();
    void Display() const;
private:

    //CONST float SIZE;
    float rotSpeed = .1;
    float rot;

    QVector3D position; // XYZ
    float hbSize = 82; // Taille de la hitbox
    GLUquadric *quad;

    GLuint *texture; // Texture

    void DrawPillar(float size) const;

    QElapsedTimer timer; // For lights

};

#endif // STATION_H
