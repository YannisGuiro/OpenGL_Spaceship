#include "station.h"

Station::Station()
{
    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad,GLU_FILL);

    position[0] = 300;
    position[1] = 0;
    position[2] = 0;


    int nb_textures = 20;
    texture = new GLuint[nb_textures];
    glGenTextures(nb_textures, texture);

    //// TEXTURE STATION
    glEnable(GL_TEXTURE_2D);
    //
    QImage im0(":/ressources/panel.png");
    im0 = im0.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //
    QImage im1(":/ressources/panel_side.png");
    im1 = im1.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //
    QImage im2(":/ressources/top_wing.png");
    im2 = im2.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //
    QImage im3(":/ressources/side_wing.png");
    im3 = im3.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im3.width(), im3.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im3.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im4(":/ressources/mid_sides.png");
    im4 = im4.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im4.width(), im4.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im4.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im5(":/ressources/mid_light.png");
    im5 = im5.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im5.width(), im5.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im5.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im6(":/ressources/cyl_mid.png");
    im6 = im6.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im6.width(), im6.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im6.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im7(":/ressources/cyl_top_1.png");
    im7 = im7.convertToFormat(QImage::Format_RGBA8888);

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im7.width(), im7.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im7.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage im8(":/ressources/base.jpg");
    im8 = im8.convertToFormat(QImage::Format_RGBA8888);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, im8.width(), im8.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im8.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    gluQuadricTexture(quad, true);
    glDisable(GL_TEXTURE_2D);
    timer.start();
}

Station::~Station()
{
    delete[] texture;
    gluDeleteQuadric(quad);
}

void Station::Update()
{
    rot += rotSpeed;
}

void Station::Display() const
{
    glPushMatrix();

    glEnable(GL_LIGHTING);
    glTranslated(position[0],position[1],position[2]);
    glRotated(-80,1,0,0);
    glRotated(rot,0,0,1); //rot
    glEnable(GL_TEXTURE_2D);


    GLfloat matEmission[] = {1,1,1,1};
    GLfloat matEmissionDefault[] = {0,0,0,1};



    if(timer.elapsed()%1000 <= 666 && timer.elapsed()%1000 >= 333) // Every 500 ms
    {
       glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
    }

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glColor3ub(255,255,255);
    gluCylinder(quad, 70, 70, 2, 40, 4);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);

    //glTranslated(0,0,2);
    //gluCylinder(quad, 60, 20, 12, 20, 8);

    //// BOTTOM PART (CYLINDERS)
    glPushMatrix();
    glRotated(180,0,1,0);

    glBindTexture(GL_TEXTURE_2D, texture[7]);  gluCylinder(quad, 70, 40, 10, 40, 10);

    glTranslated(0,0,10);
    if(timer.elapsed()%1000 <= 333 && timer.elapsed()%1000 >= 0) // Every 500 ms
    {
       glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
    }
    glBindTexture(GL_TEXTURE_2D, texture[6]);  gluCylinder(quad, 40, 40, 1, 40, 2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);

    glTranslated(0,0,1);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 40, 27, 4, 40, 4);

    glTranslated(0,0,4);
    if(timer.elapsed()%1000 <= 999 && timer.elapsed()%1000 >= 666) // Every 500 ms
    {
       glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
    }
    glBindTexture(GL_TEXTURE_2D, texture[6]);  gluCylinder(quad, 27, 27, 1, 40, 2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);

    glTranslated(0,0,1);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 24, 27, 40, 3);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 24, 18, 10, 40, 10);


    glTranslated(0,0,10);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 12, 18, 40, 3);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 12, 11, 8, 40, 10);

    glTranslated(0,0,8);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 10, 11, 40, 3);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 10, 9, 1, 40, 3);

    glTranslated(0,0,1);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 9, 9, 20, 40, 20);

    glTranslated(0,0,20);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 9, 7, 4, 40, 5);

    glTranslated(0,0,4);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 0, 7, 40, 5);
    glPopMatrix();

    //// TOP PART (CYLINDERS)
    glPushMatrix();
    glTranslated(0,0,2);
    glColor3ub(255,255,255);

    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 70, 40, 10, 40, 10);

    glTranslated(0,0,10);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 35, 40, 40, 3);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 35, 18, 4, 40, 4);


    glTranslated(0,0,4);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 16, 18, 40, 3);

    glTranslated(0,0,-1);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 14, 16, 1, 40, 3);

    glTranslated(0,0,-2);
    glBindTexture(GL_TEXTURE_2D, texture[6]); gluCylinder(quad, 12, 14, 2, 40, 3);

    glTranslated(0,0,-4);
    glBindTexture(GL_TEXTURE_2D, texture[7]); gluCylinder(quad, 10, 12, 4, 40, 3);
    glBindTexture(GL_TEXTURE_2D, texture[8]); gluDisk(quad, 0, 10, 40, 5);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    // On recentre
    glTranslated(0,0,1);
    glPushMatrix();
    // Boucle pour les 4 faces
    for(int i=0; i<4; i++)
    {
        glRotated(90,0,0,1);
        glColor3ub(255,255,255);

        glEnable(GL_TEXTURE_2D);

        //// CENTER PART
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);

        glBindTexture(GL_TEXTURE_2D, texture[4]);
        glBegin(GL_QUAD_STRIP);
        glTexCoord2d(1,1);     glVertex3d(-6,75,-2); glTexCoord2d(1,0);     glVertex3d(-6,62,-2);
        glTexCoord2d(.75,1);   glVertex3d(-6,75,2);  glTexCoord2d(.75,0);   glVertex3d(-6,62,2);
        glTexCoord2d(0,1);     glVertex3d(6,75,2);   glTexCoord2d(0,0);     glVertex3d(6,62,2);
        glEnd();

        glBegin(GL_QUAD_STRIP);
        glTexCoord2d(1,1);   glVertex3d(6,75,2);   glTexCoord2d(1,0);   glVertex3d(6,62,2);
        glTexCoord2d(.75,1); glVertex3d(6,75,-2);  glTexCoord2d(.75,0); glVertex3d(6,62,-2);
        glTexCoord2d(0,1);   glVertex3d(-6,75,-2); glTexCoord2d(0,0);   glVertex3d(-6,62,-2);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[5]);
        glBegin(GL_QUADS);
        glTexCoord2d(0,1);     glVertex3d(-6,75,-2);
        glTexCoord2d(0,0);     glVertex3d(-6,75,2);
        glTexCoord2d(1,0);     glVertex3d(6,75,2);
        glTexCoord2d(1,1);     glVertex3d(6,75,-2);
        glEnd();

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);


        //// TOP PART (TOP)
        glColor3ub(255,255,255);
        glBindTexture(GL_TEXTURE_2D, texture[2]); // Front
        glBegin(GL_QUADS);
        glTexCoord2d(0,1); glVertex3d(5.5,73,2);     glTexCoord2d(1,1); glVertex3d(-5.5,73,2);
        glTexCoord2d(1,0); glVertex3d(-5.5,73,40);   glTexCoord2d(0,0); glVertex3d(5.5,73,40);

        glTexCoord2d(.103, .894); glVertex3d(-5.5,73,40);   glTexCoord2d(.875, .894); glVertex3d(5.5,73,40);
        glTexCoord2d(.875, .980); glVertex3d(5.5,68,40);    glTexCoord2d(.103, .980); glVertex3d(-5.5,68,40);
        glEnd();


        glDisable(GL_TEXTURE_2D); glColor3ub(128,128,128);
        glBegin(GL_QUADS);
        glTexCoord2d(.875, .980); glVertex3d(5.5,68,40);    glTexCoord2d(.103, .980); glVertex3d(-5.5,68,40);
        glTexCoord2d(1,1); glVertex3d(-5.5,54,19);   glTexCoord2d(1,0); glVertex3d(5.5,54,19);

        glTexCoord2d(1,1); glVertex3d(-5.5,54,19);   glTexCoord2d(1,0); glVertex3d(5.5,54,19);
        glTexCoord2d(0,1); glVertex3d(5.5,48,14);   glTexCoord2d(0,0); glVertex3d(-5.5,48,14);

        glTexCoord2d(0,1); glVertex3d(5.5,48,14);   glTexCoord2d(0,0); glVertex3d(-5.5,48,14);
        glTexCoord2d(1,1); glVertex3d(-5.5,45,12);   glTexCoord2d(1,0); glVertex3d(5.5,45,12);

        glTexCoord2d(1,1); glVertex3d(-5.5,45,12);   glTexCoord2d(1,0); glVertex3d(5.5,45,12);
        glTexCoord2d(0,1); glVertex3d(5.5,40,11);   glTexCoord2d(0,0); glVertex3d(-5.5,40,11);

        glTexCoord2d(0,1); glVertex3d(5.5,40,11);   glTexCoord2d(0,0); glVertex3d(-5.5,40,11);
        glTexCoord2d(1,1); glVertex3d(-5.5,37,10.8); glTexCoord2d(1,0); glVertex3d(5.5,37,10.8);
        glEnd();
        glEnable(GL_TEXTURE_2D);


        //// TOP PART (SIDES)
        glBindTexture(GL_TEXTURE_2D, texture[3]);

        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        // ( pour calculer les coordonnées des textures : simple produit en croix en supposant que le polygone est dans un carré)
        glTexCoord2d(0, 1);     glVertex3d(5.5,73,2);
        glTexCoord2d(1, 1);     glVertex3d(5.5,73,40);
        glTexCoord2d(1, .85);   glVertex3d(5.5,68,40);
        glTexCoord2d(.44, .45); glVertex3d(5.5,54,19);
        glTexCoord2d(.31, .28); glVertex3d(5.5,48,14);
        glTexCoord2d(.26, .2);  glVertex3d(5.5,45,12);
        glTexCoord2d(.23, .06); glVertex3d(5.5,40,11);
        glTexCoord2d(.23, 0);   glVertex3d(5.5,38,10.8);
        glTexCoord2d(0,0);      glVertex3d(5.5,38,2);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1);     glVertex3d(-5.5,73,2);
        glTexCoord2d(1, 1);     glVertex3d(-5.5,73,40);
        glTexCoord2d(1, .85);   glVertex3d(-5.5,68,40);
        glTexCoord2d(.44, .45); glVertex3d(-5.5,54,19);
        glTexCoord2d(.31, .28); glVertex3d(-5.5,48,14);
        glTexCoord2d(.26, .2);  glVertex3d(-5.5,45,12);
        glTexCoord2d(.23, .06); glVertex3d(-5.5,40,11);
        glTexCoord2d(.23, 0);   glVertex3d(-5.5,37,10.8);
        glTexCoord2d(0,0);      glVertex3d(-5.5,38,2);
        glEnd();


        //// BOTTOM PART (BACK)
        glColor3ub(255,255,255);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_QUADS);
        // Front
        glTexCoord2d(1, 0); glVertex3d(-8, 73, -5);     glTexCoord2d(0, 0); glVertex3d(8, 73, -5);
        glTexCoord2d(.25 , 1); glVertex3d(4, 73, -30);  glTexCoord2d(.75, 1); glVertex3d(-4, 73, -30);
        // Down
        glTexCoord2d(.75 , 1); glVertex3d(-4, 73, -30);  glTexCoord2d(.25 , 1); glVertex3d(4, 73, -30);
        glTexCoord2d(.25 , .8);  glVertex3d(4, 70, -30); glTexCoord2d(.75 , .8);  glVertex3d(-4, 70, -30);
        // Back
        glTexCoord2d(1, 0); glVertex3d(-8, 70, -5);     glTexCoord2d(0, 0); glVertex3d(8, 70, -5);
        glTexCoord2d(.25 , 1); glVertex3d(4, 70, -30);  glTexCoord2d(.75, 1); glVertex3d(-4, 70, -30);
        // Up
        glTexCoord2d(1 , 1); glVertex3d(-8, 73, -5);  glTexCoord2d(0 , 1); glVertex3d(8, 73, -5);
        glTexCoord2d(0 , .8);  glVertex3d(8, 70, -5); glTexCoord2d(1 , .8);  glVertex3d(-8, 70, -5);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBegin(GL_QUADS);
        // Sides
        glTexCoord2d(0 , 1); glVertex3d(4, 70, -30);   glTexCoord2d(1 , 1); glVertex3d(4, 73, -30);
        glTexCoord2d(1 , 0); glVertex3d(8, 73, -5);   glTexCoord2d(0 , 0); glVertex3d(8, 70, -5);
        //
        glTexCoord2d(0 , 1); glVertex3d(-4, 70, -30);   glTexCoord2d(1 , 1); glVertex3d(-4, 73, -30);
        glTexCoord2d(1 , 0); glVertex3d(-8, 73, -5);   glTexCoord2d(0 , 0); glVertex3d(-8, 70, -5);
        glEnd();

        //// BOTTOM PART (BOTTOM)
        glColor3ub(122,122,122);
        glBegin(GL_QUAD_STRIP);
        glVertex3d(-3.7, 70, -27.5); glVertex3d(3.7, 70, -27.5);
        glVertex3d(-3.7, 67, -25);   glVertex3d(3.7, 67, -25);
        glVertex3d(-3.7, 58, -2);    glVertex3d(3.7, 58, -2);
        glVertex3d(-3.7, 68, -2);    glVertex3d(3.7, 68, -2);
        glVertex3d(-3.7, 70, -7);    glVertex3d(3.7, 70, -7);
        glEnd();

        //// BOTTOM PART (SIDES)
        glColor3ub(122,122,122);
        glBegin(GL_POLYGON);
        glVertex3d(-3.7, 70, -27.5);
        glVertex3d(-3.7, 67, -25);
        glVertex3d(-3.7, 58, -2);
        glVertex3d(-3.7, 68, -2);
        glVertex3d(-3.7, 70, -7);
        glEnd();

        glColor3ub(122,122,122);
        glBegin(GL_POLYGON);
        glVertex3d(3.7, 70, -27.5);
        glVertex3d(3.7, 67, -25);
        glVertex3d(3.7, 58, -2);
        glVertex3d(3.7, 68, -2);
        glVertex3d(3.7, 70, -7);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        //// LIGHT PILLARS THINGY
        glPushMatrix();
        glTranslated(2, 70, 40);
        DrawPillar(20);
        glTranslated(-3, 0, 0);
        DrawPillar(35);
        glPopMatrix();
    }


    glPopMatrix();

    glEnable(GL_CULL_FACE);

    glTranslated(0,0,5);

    // Dessin de la hitbox, qui est pour l'instant (voir indéfiniment) une sphère, car moins compliqué à mettre en place
    glColor4ub(0, 255, 200, 40);
    gluSphere(quad, hbSize, 30, 30);

    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glPopMatrix();
}

void Station::DrawPillar(float size) const
{
    glPushMatrix();
    GLfloat matEmissionPillar[] = {.5,.5,1,1};
    GLfloat matEmissionDefault[] = {0,0,0,1};
    glColor3ub(125,125,125);
    gluCylinder(quad, .7, .7, size, 4, 1);
    glTranslated(0, 0, size);
    glColor3ub(125,125,255);
    if(timer.elapsed()%1000 <= 500) // Every 500 ms
    {
       glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionPillar);
    }
    gluSphere(quad, 1, 6, 6);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);

    glPopMatrix();
}


