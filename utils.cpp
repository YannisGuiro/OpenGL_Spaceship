#include"utils.h"

bool checkCollisionSphereSphere(QVector3D pos1, float size1, QVector3D pos2, float size2)
{
    QVector3D vecd = pos1 - pos2;
    float distance = vecd.length();
    return (distance < (size1+size2));
}

//bool checkCollisionSphereCylinder(QVector3D pos1, float size1, QVector3D pos2, float size2, float height, QVector3D rotation)
//{
//    // On fait la même qu'avec le cercle, mais plus ou moins comme si le cylindre était constitué de plusieurs cercles empilés.
//    // Il nous faut alors obligatoirement l'angle de rotation du cylindre
//    QVector3D pos_inc;

//    for(int i = )
//    QVector3D vecd = pos1 - pos2;
//    float distance = vecd.length();
//    return (distance < (size1+size2));
//}
