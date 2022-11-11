#ifndef UTILS_H
#define UTILS_H
#include <QVector3D>


#endif // UTILS_H

// Mainly for collisions
// Check http://www.realtimerendering.com/intersections.html for more info / other shapes
bool checkCollisionSphereSphere(QVector3D pos1, float size1, QVector3D pos2, float size2);

