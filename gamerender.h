#include "universe.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>

// Classe dediée a l'affichage d'une scene OpenGL
class GameRender : public QOpenGLWidget
{
    Q_OBJECT
public:

    // Constructeur
    GameRender(QWidget * parent = nullptr);
    ~GameRender();

    void reset();
    void setAsteroid(int nb);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de reset de tout

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction qui bouge la caméra avec le gluLookAt
    void moveCamera();
    // Fonction d'affichage
    void paintGL();

    // Fonction de mise en lace des lumières
    void setupLight();




private:
    int keyV{0}, keyH{0}, space{0}; // To register keypresses
    float depth{7}; // Defines how far the camera is for the player

    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;

    QVector3D posCamera{10,100,1000}; // Position of camera in the XYZ
    float angleCamera{0};

    // Create our objects
    Ship* player = nullptr;
    Universe* universe = nullptr;
    Asteroid* asteroids;
    int nb_asteroids = 100; // Nombre d'astéroïdes
    Station* station;

    bool hasWon = false;


public slots:
    void keyPressReceiveEvent(int key);
    void keyReleaseReceiveEvent(int key);

signals:
    void hit();
    void end();
    void restart();
    void close();
};
