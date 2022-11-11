#include "universe.h"
#include<QImage>
#include<QDebug>
#include<QtMath>
#include<QCoreApplication>
#include<QDir>

Universe::Universe(Asteroid* asts, int nb_asts, Station* st, Ship* player)
{
    quad = gluNewQuadric();

    // On prends les asteroids/station de gamerender en pointur d'abord
    station = st;
    asteroids = asts;
    nb_asteroids = nb_asts;


    //// TEXTURE UNIVERS
    QImage im(":/ressources/space2.jpg");
    im = im.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &sp_texture);

    glBindTexture(GL_TEXTURE_2D, sp_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im.width(), im.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    //// INIT/ressources ASTEROIDES
    // Initialisation de la texture de l'astéroïde.
    QImage ast_im1(":/ressources/asteroid.jpg");
    ast_im1 = ast_im1.convertToFormat(QImage::Format_RGBA8888);
    QImage ast_im2(":/ressources/asteroid2.jpg");
    ast_im2 = ast_im2.convertToFormat(QImage::Format_RGBA8888);
    QImage ast_im3(":/ressources/asteroid3.jpg");
    ast_im3 = ast_im3.convertToFormat(QImage::Format_RGBA8888);
    QImage ast_im4(":/ressources/asteroid4.jpg");
    ast_im4 = ast_im4.convertToFormat(QImage::Format_RGBA8888);

    // Elle est choisit aléatoirement entre quelques textures.
    GLuint* ast_texture = new GLuint[4];
    glGenTextures(4, ast_texture);
    glBindTexture(GL_TEXTURE_2D, ast_texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ast_im1.width(), ast_im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ast_im1.bits());
    glBindTexture(GL_TEXTURE_2D, ast_texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ast_im2.width(), ast_im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ast_im2.bits());
    glBindTexture(GL_TEXTURE_2D, ast_texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ast_im3.width(), ast_im3.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ast_im3.bits());
    glBindTexture(GL_TEXTURE_2D, ast_texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ast_im4.width(), ast_im4.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ast_im4.bits());

    for(int i = 0; i<4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, ast_texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    for(int i = 0 ; i < nb_asteroids ; i++)
    {
        asteroids[i].Initialize(ast_delim, asteroids, i, station, player);
        asteroids[i].setTexture(ast_texture[rand()%4]); // Choix d'une des 4 texture
    }




}

Universe::~Universe()
{
    delete[] asteroids;
    gluDeleteQuadric(quad);
}



void Universe::Update()
{
    for(int i = 0 ; i < nb_asteroids ; i++)
    {
        asteroids[i].Update();
    }
    station->Update();
}

void Universe::Display(QVector3D pos) const{

    glPushMatrix();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslated(pos.x(), pos.y(), pos.z()); // Permet au 'fond' de suivre le joueur, donnant une impression d'infini
    glColor4f(1,1,1,1); // Blanc pour ne pas influencer sur la texture

    glBindTexture(GL_TEXTURE_2D, sp_texture);
    gluQuadricDrawStyle(quad,GLU_FILL);
    gluQuadricTexture(quad, true);
    gluSphere(quad, 1000, 10, 10);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();





    //// Astéroides
    for(int i = 0 ; i < nb_asteroids ; i++)
    {
        asteroids[i].Display();
    }

    //// Station
    station->Display();

    // Sphere pour connaitre la délimitation des astéroides
    // Si on s'en approche trop elle devient visible
    double distFromPlayer = ast_delim - qPow(pos.x()*pos.x() + pos.y()*pos.y() + pos.z()*pos.z(),.5f);
    double alphaOutline = distFromPlayer > 70 ? 0 : (70-distFromPlayer)*(255/70);
    glColor4ub(255, 0, 0, alphaOutline);
    gluQuadricDrawStyle(quad,GLU_LINE);
    gluSphere(quad, ast_delim ,100, 100);

}

