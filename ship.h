#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include<QQuaternion>
// Classe dediee pour la gestion du vaisseau
class Ship
{
public:
    // Constructeur
    Ship();

    // Destructeur
    ~Ship();
    // Update position
    void Update(int, int, int);

    // Reset posisition
    void Reset();

    // Methode d'affichage
    void Display() const;
    void DrawFire() const;

    // Inline getters
    QQuaternion getQuat() {return quat;};


    float getPosX(){ return pos[0]; }
    float getPosY(){ return pos[1]; }
    float getPosZ(){ return pos[2]; }
    QVector3D getPos(){ return pos; }


    float getHitBoxSize() { return hbSize;}

    double* getNormal(double*, double*, double*);



private:
    GLUquadric *quad;
    float hbSize = 1.5;

    double *v[40]; // Liste des tous les vertices
    double *n[100]; // Liste des toutes les normales, plus pratique

    // Toutes les variables qui définissent position et rotation du vaisseau
    QVector3D pos;
    float pitch = 0, roll = 0, yaw = 0;
    float x, y, z, angle;
    bool isAdvancing = false;
    QQuaternion quat;

    GLuint *texture; // Textures



    float movSpeed = .5;
    float rotSpeed = 2;

};
