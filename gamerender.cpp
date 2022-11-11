#include "gamerender.h"
#include "utils.h"
#include <QApplication>
#include <GL/glu.h>
#include <algorithm>
// Declarations des constantes
const unsigned int WINH = 800;
const unsigned int WINW = 1300;


// Constructeur
GameRender::GameRender(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
       setFixedSize(WINW, WINH);

       // Connexion du timer
       connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
           m_TimeElapsed += 1.0f;

           update();
       });

       m_AnimationTimer.setInterval(15);
       m_AnimationTimer.start();
    setFixedSize(WINW, WINH);
}



// Destructeur
GameRender::~GameRender()
{
    delete player;
    delete universe;
}



// Fonction d'initialisation
void GameRender::initializeGL()
{
    srand(time(NULL)); // Seed aléatoire pour les astéroïdes notamment.
    // Enables and all
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

    ///glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE);


    /// INITIALISATION DES OBJETS
    qDebug() << "Initialisation";
    player = new Ship();
    qDebug() << "Ship initialized";

    station = new Station();
    qDebug() << "Station initialized";

    asteroids = new Asteroid[nb_asteroids];
    qDebug() << "Asteroids initialized";

    universe = new Universe(asteroids, nb_asteroids, station, player);
    qDebug() << "Universe initialized";
}

void GameRender::reset()
{
    /// INITIALISATION DES OBJETS
    qDebug() << "Nouvelle initialisation";
    player = new Ship();
    qDebug() << "Ship initialized";

    station = new Station();
    qDebug() << "Station initialized";

    asteroids = new Asteroid[nb_asteroids];
    qDebug() << "Asteroids initialized";

    universe = new Universe(asteroids, nb_asteroids, station, player);
    qDebug() << "Universe initialized";

    hasWon = false;
}

void GameRender::setAsteroid(int nb){
    nb_asteroids = nb;
}

// Fonction de redimensionnement
void GameRender::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}


// Fonction d'affichage
void GameRender::paintGL()
{
    glClearColor(.5,.5,.5, 0.);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Update positions
    universe->Update();
    if(!hasWon)  player->Update(keyV, keyH, space);


    /// Detection des hitboxes

    // Check for collisions between player and asteroids !
    for(int i = 0 ; i < nb_asteroids ; i++)
    {
        if(checkCollisionSphereSphere(player->getPos(), player->getHitBoxSize(), asteroids[i].getPos(), asteroids[i].getRad()))
        {
            qDebug() << "Collision between asteroid n°" << i << " and the player ! Resetting.";
            player->Reset();
            emit hit();
        }
    }

    // Check for collision between station and player
    if(checkCollisionSphereSphere(player->getPos(), player->getHitBoxSize(), station->getHitBoxPos(), station->getHitboxSize()))
    {

        if(!hasWon)
        {
            qDebug() << "Collision between station and player !";
            emit end();
        }
        hasWon = true;


    }


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, float(WINW)/float(WINH), depth/1.7 /*.1f*/, 2000);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    moveCamera(); // Positions camera behind the player

    setupLight();


    // Diplay entities
    player->Display();
    universe->Display(player->getPos());


}





// Fonction qui bouge la caméra
void GameRender::moveCamera()
{
    QVector3D aimCamera;
    QQuaternion q = player->getQuat();

    // On crée un vecteur qui permet de définir un vecteur partant de la caméra pour aller vers le vaisseau
    // On part du principe qu'elle a une hauteur de depth/2 et est reculée de depth par rapport au vaisseau.
    QVector3D directionCam = q.rotatedVector(QVector3D(0,depth/2,-depth));


    // La position vers laquelle on veut diriger la caméra
    if(!hasWon) aimCamera = player->getPos() + directionCam;
    else aimCamera = player->getPos() + q.rotatedVector(QVector3D(100,100/2,-100));


    //Permet de bouger la caméra de manière plus lisse
    posCamera += (aimCamera-posCamera) * (.08 - .07*hasWon);


    // On refait la même manip que pour la position de la caméra afin de savoir où se trouve l'axe Y du vaisseau, donc (0,1,0)
    QVector3D upward = q.rotatedVector(QVector3D(0,1,0));

    gluLookAt(
                posCamera[0],
                posCamera[1],
                posCamera[2],
                player->getPosX(), // 'Regard' en X de la caméra
                player->getPosY(),  // 'Regard' en Y de la caméra
                player->getPosZ(),  // 'Regard' en Z de la caméra
                upward[0], upward[1], upward[2]); // Le haut de la caméra en fonction de l'axe Y du vaisseau

}

void GameRender::setupLight()
{
    const float amb = .1;
    const float LightAmbient[]  = { amb, amb, amb, 1.0f };
    const float LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const float LightPosition[] = { .0f,  1.0f, 1.0f, 0.0f };
    const float LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);


    //glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient[1]);

    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR);
    //glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}




// Fonction de gestion d'interactions clavier
void GameRender::keyPressReceiveEvent(int key)
{
        switch(key)
        {
        case Qt::Key_D:
            keyH += 1;
            break;
        case Qt::Key_Q:
            keyH -= 1;
            break;
        case Qt::Key_Z:
            keyV += 1;
            break;
        case Qt::Key_S:
            keyV -= 1;
            break;
        case Qt::Key_Space:
            space += 1;
            break;
        case Qt::Key_X:
            space -= 1;
            break;
        default:
            break;

    }
}

void GameRender::keyReleaseReceiveEvent(int key)
{
    switch(key)
    {
    case Qt::Key_D:
        keyH -= 1;
        break;
    case Qt::Key_Q:
        keyH += 1;
        break;
    case Qt::Key_Z:
        keyV -= 1;
        break;
    case Qt::Key_S:
        keyV += 1;
        break;
    case Qt::Key_Space:
        space -= 1;
        break;
    case Qt::Key_X:
        space += 1;
        break;
    default:
        break;
    }
}

