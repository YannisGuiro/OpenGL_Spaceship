#include "asteroid.h"
#include "utils.h"
#include <random>
#include <math.h>
#include <QDebug>
#include<QImage>

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
    gluDeleteQuadric(quad);
}

void Asteroid::Initialize(float delim, Asteroid* asteroids, int ite, Station* st, Ship *player)
{
    this->delim = delim;

    // Génération aléatoire de multiples valeurs :
    size = rand()% SIZE_RANGE[1] + SIZE_RANGE[0];
    rotSpeedX = (float)rand() / (float)(RAND_MAX/(4)) - 2;
    rotSpeedY = fmod((float)rand(),4) - 2;

    position = generateValidPosition(delim, asteroids, ite, st, player);

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad,GLU_FILL);

}


QVector3D Asteroid::generateValidPosition(float delim, Asteroid* asteroids, int ite, Station* st, Ship *player)
{
    QVector3D pos;
    do{ pos = generate(delim); }
    while(
            checkCollisionSphereSphere(st->getHitBoxPos(), st->getHitboxSize(), pos, size) ||
            checkCollisionSphereSphere(player->getPos(), player->getHitBoxSize(), pos, size)
          );

    for(int i = 0 ; i < ite ; i++)
    {
        if(checkCollisionSphereSphere(asteroids[i].getPos(), asteroids[i].getRad(), pos, size))
        {
            do{ pos = generate(delim); } while(checkCollisionSphereSphere(st->getHitBoxPos(), st->getHitboxSize(), pos, size));
            i = 0;
        }
    }

    return pos;
}

void Asteroid::Update()
{
    rotX += rotSpeedX;
    rotY += rotSpeedY;
}


void Asteroid::Display()
{
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(position[0], position[1], position[2]);
    glRotated(rotX,1,0,0);
    glRotated(rotY,0,1,0);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, astTexture);
    gluQuadricTexture(quad, true);

    glColor3ub(255,255,255);
    gluSphere(quad, size, 20, 20);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPopMatrix();
}



QVector3D Asteroid::generate(float delim)
{
    // On génère l'aléatoire pour la distribution gaussienne.
    std::random_device rd;
    std::default_random_engine generator;
    generator.seed(rd());
    std::normal_distribution<double> distribution(0,.3);

    QVector3D pos;
    while(true) // Cas ou X=Y=Z=0
    {
        pos[0] = distribution(generator); // Distribution gaussienne, les astéroides seront plus centré.
        pos[1] = distribution(generator);
        pos[2] = distribution(generator);
        if(1/sqrt(pow(pos[0],2)+pow(pos[1],2)+pow(pos[2],2))>1) break;
    }

    pos[0] *= delim; // X
    pos[1] *= delim; // Y
    pos[2] *= delim; // Z

    return pos;
}

