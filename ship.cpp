#include "ship.h"
#include <time.h>
#include <stdlib.h>
#include<QDebug>
#include<QImage>
Ship::Ship()
{
    // Initialise la position du vaisseau loin de la station
    Reset();

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad,GLU_FILL);

    v[1]=new double[3]{-0.387542,0.412120,-0.311530};
    v[2]=new double[3]{-0.002925,0.728553,-1.006549};
    v[3]=new double[3]{-0.355893,0.039226,-0.227746};
    v[10]=new double[3]{0.360929,0.038254,-0.224704};
    v[4]=new double[3]{-0.085833,0.475896,0.381502};
    v[5]=new double[3]{-0.088359,0.863073,-0.336536};
    v[6]=new double[3]{-0.207472,0.548801,-0.151497};
    v[7]=new double[3]{0.210676,0.548235,-0.153273};
    v[8]=new double[3]{0.093371,0.475651,0.380741};
    v[9]=new double[3]{0.389012,0.411069,-0.314826};
    v[11]=new double[3]{0.090849,0.862830,-0.337296};

    v[12]=new double[3]{-0.530956,0.082162,1.190754};
    v[13]=new double[3]{-0.835741,0.078075,-0.246571};
    v[14]=new double[3]{-0.238393,0.077261,-0.249107};
    v[15]=new double[3]{-0.539268,1.104385,-1.094376};

    v[16]=new double[3]{0.836835,0.075802,-0.253673};
    v[17]=new double[3]{0.535964,1.102927,-1.098940};
    v[18]=new double[3]{0.544277,0.080705,1.186189};
    v[19]=new double[3]{0.239487,0.076615,-0.251136};

    v[20]=new double[3]{0.010390,0.255152,1.711404};
    v[21]=new double[3]{-0.775269,0.063668,-0.068198};
    v[22]=new double[3]{-1.378268,-0.041272,-1.362557};
    v[23]=new double[3]{-1.257720,-0.154623,-1.072507};
    v[24]=new double[3]{-0.687240,0.186284,-0.478221};
    v[25]=new double[3]{-0.688753,-0.030406,-0.765265};
    v[26]=new double[3]{-1.170087,-0.116546,-1.549237};
    v[27]=new double[3]{-1.556763,-0.147056,-1.160556};
    v[28]=new double[3]{-1.739911,-0.070417,-2.112491};

    v[29]=new double[3]{0.686666,0.184421,-0.484053};
    v[30]=new double[3]{0.685154,-0.032272,-0.771097};
    v[31]=new double[3]{0.777841,0.061559,-0.074790};
    v[32]=new double[3]{1.159577,-0.119709,-1.559128};
    v[33]=new double[3]{1.369540,-0.045002,-1.374221};
    v[34]=new double[3]{1.251152,-0.158027,-1.083157};
    v[35]=new double[3]{1.549456,-0.151273,-1.173743};
    v[36]=new double[3]{1.724719,-0.075120,-2.127197};


    n[0] = getNormal(v[1],v[2],v[3]);

    n[1] = getNormal(v[1],v[2],v[3]);
    n[2] = getNormal(v[4],v[5],v[6]);
    n[3] = getNormal(v[6],v[1],v[4]);
    n[4] = getNormal(v[7],v[8],v[9]);
    n[5] = getNormal(v[2],v[9],v[10]);
    n[6] = getNormal(v[11],v[8],v[7]);
    n[7] = getNormal(v[11],v[5],v[8]);
    n[8] = getNormal(v[8],v[5],v[4]);
    n[9] = getNormal(v[3],v[2],v[10]);


    n[10] = getNormal(v[12],v[13],v[14]);
    n[11] = getNormal(v[14],v[15],v[12]);
    n[12] = getNormal(v[15],v[13],v[12]);
    n[13] = getNormal(v[13],v[15],v[14]);

    n[14] = getNormal(v[16],v[17],v[18]);
    n[15] = getNormal(v[16],v[18],v[19]);
    n[16] = getNormal(v[17],v[19],v[18]);
    n[17] = getNormal(v[17],v[16],v[19]);



    n[18] = getNormal(v[2],v[6],v[5]);
    n[19] = getNormal(v[2],v[1],v[6]);
    n[20] = getNormal(v[4],v[1],v[20]);
    n[21] = getNormal(v[8],v[20],v[9]);
    n[22] = getNormal(v[10],v[9],v[20]);
    n[23] = getNormal(v[1],v[3],v[20]);
    n[24] = getNormal(v[20],v[3],v[10]);
    n[25] = getNormal(v[2],v[7],v[9]);
    n[26] = getNormal(v[11],v[2],v[5]);
    n[27] = getNormal(v[7],v[2],v[11]);
    n[28] = getNormal(v[4],v[20],v[8]);


    n[29] = getNormal(v[21],v[22],v[23]);
    n[30] = getNormal(v[24],v[22],v[21]);
    n[31] = getNormal(v[23],v[25],v[21]);
    n[32] = getNormal(v[23],v[26],v[25]);
    n[33] = getNormal(v[23],v[22],v[27]);
    n[34] = getNormal(v[27],v[26],v[23]);
    n[35] = getNormal(v[25],v[24],v[21]);
    n[36] = getNormal(v[26],v[24],v[25]);
    n[37] = getNormal(v[24],v[26],v[22]);
    n[38] = getNormal(v[22],v[26],v[28]);
    n[39] = getNormal(v[26],v[27],v[28]);
    n[40] = getNormal(v[27],v[22],v[28]);



    n[41] = getNormal(v[29],v[30],v[31]);
    n[42] = getNormal(v[32],v[29],v[33]);
    n[43] = getNormal(v[29],v[32],v[30]);
    n[44] = getNormal(v[32],v[34],v[30]);
    n[45] = getNormal(v[30],v[34],v[31]);
    n[46] = getNormal(v[35],v[32],v[36]);
    n[47] = getNormal(v[33],v[35],v[36]);
    n[48] = getNormal(v[32],v[33],v[36]);
    n[49] = getNormal(v[33],v[34],v[35]);
    n[50] = getNormal(v[33],v[34],v[35]);
    n[51] = getNormal(v[33],v[29],v[31]);
    n[52] = getNormal(v[33],v[31],v[34]);


    int nb_textures = 20;
    texture = new GLuint[nb_textures];
    glGenTextures(nb_textures, texture);

    //// TEXTURE VAISEAU
    glEnable(GL_TEXTURE_2D);
    //
    QImage im0(":/ressources/ship_gray.jpg");
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

    glDisable(GL_TEXTURE_2D);



}

Ship::~Ship()
{
    for(int i = 0; i < 40; i++)
        delete[] v[i];
    for(int i = 0; i < 100; i++)
        delete[] n[i];
    gluDeleteQuadric(quad);

    delete[] texture;
}


void Ship::Update(int vert, int hori, int space)
{
    isAdvancing = space==1 ? true : false;
    pitch = -vert * rotSpeed;
    yaw = -hori * rotSpeed;

    quat *= QQuaternion::fromEulerAngles(pitch, yaw, 0);
    quat.getAxisAndAngle(&x, &y, &z, &angle);

    QVector3D direction(0,0,1); // Avance sur l'axe des X (Z après rotation)
    direction = quat.rotatedVector(direction);

    pos += direction * movSpeed * space;
}

void Ship::Reset()
{
    pos = {-200,0,0};
    quat = QQuaternion::fromEulerAngles(0, 90, 0);
}


void Ship::Display() const
{
    glPushMatrix();
    glTranslated(pos[0], pos[1], pos[2]);
    glRotated(angle, x, y, z);

    glBegin(GL_TRIANGLES);
    //Window
    glColor3ub(0,0,0);
    glNormal3dv(n[6]); glVertex3dv(v[11]); glVertex3dv(v[8]); glVertex3dv(v[7]);
    glNormal3dv(n[7]); glVertex3dv(v[11]); glVertex3dv(v[5]); glVertex3dv(v[8]);
    glNormal3dv(n[8]); glVertex3dv(v[8]); glVertex3dv(v[5]); glVertex3dv(v[4]);
    glNormal3dv(n[2]); glVertex3dv(v[4]); glVertex3dv(v[5]); glVertex3dv(v[6]);

    glEnd();


    // Right arm
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_TRIANGLES);
    glColor3ub(50,50,255);
    glNormal3dv(n[10]); glTexCoord2d(0,0); glVertex3dv(v[12]); glTexCoord2d(1,0); glVertex3dv(v[13]); glTexCoord2d(0,1); glVertex3dv(v[14]);
    glNormal3dv(n[11]); glTexCoord2d(0,0); glVertex3dv(v[14]); glTexCoord2d(1,0); glVertex3dv(v[15]); glTexCoord2d(0,1); glVertex3dv(v[12]);
    glNormal3dv(n[12]); glTexCoord2d(0,0); glVertex3dv(v[15]); glTexCoord2d(1,0); glVertex3dv(v[13]); glTexCoord2d(0,1); glVertex3dv(v[12]);
    glNormal3dv(n[13]); glTexCoord2d(0,0); glVertex3dv(v[13]); glTexCoord2d(1,0); glVertex3dv(v[15]); glTexCoord2d(0,1); glVertex3dv(v[14]);

    // Left arm
    glColor3ub(50,50,255);
    glNormal3dv(n[14]); glTexCoord2d(0,0); glVertex3dv(v[16]); glTexCoord2d(1,0); glVertex3dv(v[17]); glTexCoord2d(0,1); glVertex3dv(v[18]);
    glNormal3dv(n[15]); glTexCoord2d(0,0); glVertex3dv(v[16]); glTexCoord2d(1,0); glVertex3dv(v[18]); glTexCoord2d(0,1); glVertex3dv(v[19]);
    glNormal3dv(n[16]); glTexCoord2d(0,0); glVertex3dv(v[17]); glTexCoord2d(1,0); glVertex3dv(v[19]); glTexCoord2d(0,1); glVertex3dv(v[18]);
    glNormal3dv(n[17]); glTexCoord2d(0,0); glVertex3dv(v[17]); glTexCoord2d(1,0); glVertex3dv(v[16]); glTexCoord2d(0,1); glVertex3dv(v[19]);


    // Bottom
    glColor3ub(100,100,100);
    glNormal3dv(n[1]); glTexCoord2d(0,0); glVertex3dv(v[1]); glTexCoord2d(0,1); glVertex3dv(v[2]); glTexCoord2d(0,1); glVertex3dv(v[3]);
    glNormal3dv(n[3]); glTexCoord2d(0,0); glVertex3dv(v[6]); glTexCoord2d(0,1); glVertex3dv(v[1]); glTexCoord2d(0,1); glVertex3dv(v[4]);
    glNormal3dv(n[4]); glTexCoord2d(0,0); glVertex3dv(v[7]); glTexCoord2d(0,1); glVertex3dv(v[8]); glTexCoord2d(0,1); glVertex3dv(v[9]);
    glNormal3dv(n[5]); glTexCoord2d(0,0); glVertex3dv(v[2]); glTexCoord2d(0,1); glVertex3dv(v[9]); glTexCoord2d(0,1); glVertex3dv(v[10]);
    glNormal3dv(n[9]); glTexCoord2d(0,0); glVertex3dv(v[3]); glTexCoord2d(0,1); glVertex3dv(v[2]); glTexCoord2d(0,1); glVertex3dv(v[10]);

    // Top
    glColor3ub(255,255,255);
    glNormal3dv(n[18]); glTexCoord2d(0,0); glVertex3dv(v[2]);  glTexCoord2d(0,1); glVertex3dv(v[6]);  glTexCoord2d(0,1); glVertex3dv(v[5]);
    glNormal3dv(n[19]); glTexCoord2d(0,0); glVertex3dv(v[2]);  glTexCoord2d(0,1); glVertex3dv(v[1]);  glTexCoord2d(0,1); glVertex3dv(v[6]);
    glNormal3dv(n[20]); glTexCoord2d(0,0); glVertex3dv(v[4]);  glTexCoord2d(0,1); glVertex3dv(v[1]);  glTexCoord2d(0,1); glVertex3dv(v[20]);
    glNormal3dv(n[21]); glTexCoord2d(0,0); glVertex3dv(v[8]);  glTexCoord2d(0,1); glVertex3dv(v[20]); glTexCoord2d(0,1); glVertex3dv(v[9]);
    glNormal3dv(n[22]); glTexCoord2d(0,0); glVertex3dv(v[10]); glTexCoord2d(0,1); glVertex3dv(v[9]);  glTexCoord2d(0,1); glVertex3dv(v[20]);
    glNormal3dv(n[23]); glTexCoord2d(0,0); glVertex3dv(v[1]);  glTexCoord2d(0,1); glVertex3dv(v[3]);  glTexCoord2d(0,1); glVertex3dv(v[20]);
    glNormal3dv(n[24]); glTexCoord2d(0,0); glVertex3dv(v[20]); glTexCoord2d(0,1); glVertex3dv(v[3]);  glTexCoord2d(0,1); glVertex3dv(v[10]);
    glNormal3dv(n[25]); glTexCoord2d(0,0); glVertex3dv(v[2]);  glTexCoord2d(0,1); glVertex3dv(v[7]);  glTexCoord2d(0,1); glVertex3dv(v[9]);
    glNormal3dv(n[26]); glTexCoord2d(0,0); glVertex3dv(v[11]); glTexCoord2d(0,1); glVertex3dv(v[2]);  glTexCoord2d(0,1); glVertex3dv(v[5]);
    glNormal3dv(n[27]); glTexCoord2d(0,0); glVertex3dv(v[7]);  glTexCoord2d(0,1); glVertex3dv(v[2]);  glTexCoord2d(0,1); glVertex3dv(v[11]);
    glNormal3dv(n[28]); glTexCoord2d(0,0); glVertex3dv(v[4]);  glTexCoord2d(0,1); glVertex3dv(v[20]); glTexCoord2d(0,1); glVertex3dv(v[8]);


    // Right wing
    glNormal3dv(n[29]); glTexCoord2d(0,0); glVertex3dv(v[21]); glTexCoord2d(0,1); glVertex3dv(v[22]); glTexCoord2d(0,1); glVertex3dv(v[23]);
    glNormal3dv(n[30]); glTexCoord2d(0,0); glVertex3dv(v[24]); glTexCoord2d(0,1); glVertex3dv(v[22]); glTexCoord2d(0,1); glVertex3dv(v[21]);
    glNormal3dv(n[31]); glTexCoord2d(0,0); glVertex3dv(v[23]); glTexCoord2d(0,1); glVertex3dv(v[25]); glTexCoord2d(0,1); glVertex3dv(v[21]);
    glNormal3dv(n[32]); glTexCoord2d(0,0); glVertex3dv(v[23]); glTexCoord2d(0,1); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[25]);
    glNormal3dv(n[33]); glTexCoord2d(0,0); glVertex3dv(v[23]); glTexCoord2d(0,1); glVertex3dv(v[22]); glTexCoord2d(0,1); glVertex3dv(v[27]);
    glNormal3dv(n[34]); glTexCoord2d(0,0); glVertex3dv(v[27]); glTexCoord2d(0,1); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[23]);
    glNormal3dv(n[35]); glTexCoord2d(0,0); glVertex3dv(v[25]); glTexCoord2d(0,1); glVertex3dv(v[24]); glTexCoord2d(0,1); glVertex3dv(v[21]);
    glNormal3dv(n[36]); glTexCoord2d(0,0); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[24]); glTexCoord2d(0,1); glVertex3dv(v[25]);
    glNormal3dv(n[37]); glTexCoord2d(0,0); glVertex3dv(v[24]); glTexCoord2d(0,1); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[22]);
    glNormal3dv(n[38]); glTexCoord2d(0,0); glVertex3dv(v[22]); glTexCoord2d(0,1); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[28]);
    glNormal3dv(n[39]); glTexCoord2d(0,0); glVertex3dv(v[26]); glTexCoord2d(0,1); glVertex3dv(v[27]); glTexCoord2d(0,1); glVertex3dv(v[28]);
    glNormal3dv(n[40]); glTexCoord2d(0,0); glVertex3dv(v[27]); glTexCoord2d(0,1); glVertex3dv(v[22]); glTexCoord2d(0,1); glVertex3dv(v[28]);


    // Left wing
    glNormal3dv(n[41]); glTexCoord2d(0,0); glVertex3dv(v[29]); glTexCoord2d(0,1); glVertex3dv(v[30]); glTexCoord2d(0,1); glVertex3dv(v[31]);
    glNormal3dv(n[42]); glTexCoord2d(0,0); glVertex3dv(v[32]); glTexCoord2d(0,1); glVertex3dv(v[29]); glTexCoord2d(0,1); glVertex3dv(v[33]);
    glNormal3dv(n[43]); glTexCoord2d(0,0); glVertex3dv(v[29]); glTexCoord2d(0,1); glVertex3dv(v[32]); glTexCoord2d(0,1); glVertex3dv(v[30]);
    glNormal3dv(n[44]); glTexCoord2d(0,0); glVertex3dv(v[32]); glTexCoord2d(0,1); glVertex3dv(v[34]); glTexCoord2d(0,1); glVertex3dv(v[30]);
    glNormal3dv(n[45]); glTexCoord2d(0,0); glVertex3dv(v[30]); glTexCoord2d(0,1); glVertex3dv(v[34]); glTexCoord2d(0,1); glVertex3dv(v[31]);
    glNormal3dv(n[46]); glTexCoord2d(0,0); glVertex3dv(v[35]); glTexCoord2d(0,1); glVertex3dv(v[32]); glTexCoord2d(0,1); glVertex3dv(v[36]);
    glNormal3dv(n[47]); glTexCoord2d(0,0); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[35]); glTexCoord2d(0,1); glVertex3dv(v[36]);
    glNormal3dv(n[48]); glTexCoord2d(0,0); glVertex3dv(v[32]); glTexCoord2d(0,1); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[36]);
    glNormal3dv(n[49]); glTexCoord2d(0,0); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[34]); glTexCoord2d(0,1); glVertex3dv(v[35]);
    glNormal3dv(n[50]); glTexCoord2d(0,0); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[34]); glTexCoord2d(0,1); glVertex3dv(v[35]);
    glNormal3dv(n[51]); glTexCoord2d(0,0); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[29]); glTexCoord2d(0,1); glVertex3dv(v[31]);
    glNormal3dv(n[52]); glTexCoord2d(0,0); glVertex3dv(v[33]); glTexCoord2d(0,1); glVertex3dv(v[31]); glTexCoord2d(0,1); glVertex3dv(v[34]);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    // Moteur
    GLfloat matEmissionFire[] = {1,.6,0,1};
    GLfloat matEmissionDefault[] = {0,0,0,1};
    glPushMatrix();
    glTranslated(0,.3,-.8);
    glColor3ub(100,100,100);
    gluCylinder(quad, .15, .2, .6, 20, 20);
    glColor3ub(50,50,50);
    gluCylinder(quad, .15, .08, .1, 20, 20);
    glTranslated(0,0,.1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionFire);
    gluDisk(quad,0,.08,30,2);
    DrawFire();
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmissionDefault);
    glPopMatrix();

    /// Hitbox debug sphere
//    glColor4ub(255,50,50, 100);
//    gluSphere(quad, hbSize, 10, 10);


    glPopMatrix();

}

void Ship::DrawFire() const
{
    //    glTranslated(0,0,-1);
    //    gluCylinder(quad, .0, .08 , 1, 10, 10);
}



double* Ship::getNormal(double* d1, double* d2, double *d3)
{
    double* res;

    QVector3D qv1 = QVector3D(d1[0], d1[1], d1[2]);
    QVector3D qv2 = QVector3D(d2[0], d2[1], d2[2]);
    QVector3D qv3 = QVector3D(d3[0], d3[1], d3[2]);


    QVector3D qres = QVector3D::normal(qv1, qv2, qv3);
    qres.normalize();


    res = new double[3]{qres[0], qres[1], qres[2]};
    return res;
}
