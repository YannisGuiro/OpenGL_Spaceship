#include "webcam.h"
#include <QDebug>
#include <QPainter>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

using namespace cv;
using namespace std;

const int Z = 0;
const int Q = 1;
const int S = 2;
const int D = 3;
const int SPACE = 4;

WebCam::WebCam(QWidget *parent)
    : QGraphicsView{parent}
{
    for(unsigned int i = 0; i < 5; i++){
        touches_last[i] = false;
    }
    int frameWidth=this->width();
    int frameHeight=this->height();
    op = new QGraphicsOpacityEffect(this);
    op->setOpacity(0.75); //0 to 1 will cause the fade effect to kick in
    this->setGraphicsEffect(op);
    this->setAutoFillBackground(true);
    cap = new VideoCapture(0); // open the default camera
    cout<<"width :"<<cap->get(CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height :"<<cap->get(CAP_PROP_FRAME_HEIGHT)<<endl;
    cap->set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap->set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap->isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        return;
    }

    QString sPath = QCoreApplication::applicationDirPath().append("/fist.xml");
    QFile::copy(":/fist.xml" , sPath);
    //fist_cascade = new cv::CascadeClassifier(sPath.toStdString());

    QString sPath2 = QCoreApplication::applicationDirPath().append("/palm.xml");
    QFile::copy(":/palm.xml" , sPath2);
    //palm_cascade = new cv::CascadeClassifier(sPath2.toStdString());


    //std::cout << sPath.toStdString();
   // QFile file("./debug/fist.xml");
    //qDebug () << file.exists();
    //qDebug() << QDir::currentPath();
    //qDebug() << QCoreApplication::applicationDirPath();


    fist_cascade = new CascadeClassifier();
    qDebug() << sPath;
    if( !fist_cascade->load( "./debug/fist.xml" ) )
    {
        cerr<<"Error loading haarcascade 1"<<endl;

        return;
    }

    palm_cascade = new CascadeClassifier();
    if( !palm_cascade->load( "./debug/palm.xml" ) )
    {
        cerr<<"Error loading haarcascade 2"<<endl;
        return;
    }

    timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();
    //connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    scene = new QGraphicsScene();
    this->setScene(scene);
    qDebug() << "end!";


}

void WebCam::refresh(){
    //Z Q S D Space
    for(unsigned int i = 0; i < 5; i++){
        touches[i] = false;
    }
    // Init output window
    Mat frame,frame_gray;
    std::vector<Rect> fist;
    std::vector<Rect> palm;
    // Get frame
    *cap >> frame;
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    // Equalize graylevels
    //        equalizeHist( frame_gray, frame_gray );
    // -- Detect faces
    fist_cascade->detectMultiScale( frame_gray, fist, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    if (fist.size()>0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)fist.size();i++)
            rectangle(frame,fist[i],Scalar(0,255,0),2);
    }

    palm_cascade->detectMultiScale( frame_gray, palm, 1.1, 4, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );
    if (palm.size()>0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)palm.size();i++)
            rectangle(frame,palm[i],Scalar(255,0,0),2);
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    cvtColor(frame, frame, COLOR_BGR2RGB);
    QPixmap p = QPixmap::fromImage(QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step1(), QImage::Format_RGB888));


    QPixmap pixmaptemp = p.scaled(width(),height());
    scene->clear();
    scene->addPixmap(pixmaptemp);
    this->fitInView(0,0,this->width(), this->height(),Qt::KeepAspectRatio);

    //for (int i=0;i<(int)palm.size();i++) qDebug() << "palm[" << i << "]: " << palm[i].x << " " << palm[i].y; //x de gauche de droite et y de haut en bas
    //qDebug() << "Frame size: " << frame.rows << " " << frame.cols; //y = rows, x = cols ............... cols = 320, rows = 180

    //Détection des mains ouvertes

    ////////////////////


    //Checker les fist seulement si pas de palm détecté (en mode course et pas en mode sur place)
    if ((int)palm.size() == 0 && (int)fist.size() != 0){
        //checkHands(fist, frame.rows);
        touches[SPACE] = true;
    } else if ((int)palm.size() != 0) {
        checkHands(palm, frame.rows);
    }

    //Puis attriution finale

    for(unsigned int i = 0; i < 5; i++){
        if (touches_last[i] != touches[i]){
            touches_last[i] = touches[i];

            Qt::Key key;
            switch (i){
            case (Z):
                key = Qt::Key_Z;
                break;
            case (Q):
                key = Qt::Key_Q;
                break;
            case (S):
                key = Qt::Key_S;
                break;
            case (D):
                key = Qt::Key_D;
                break;
            case (SPACE):
                key = Qt::Key_Space;
                break;

            }

            emit sendKey(key, touches_last[i]);
        }
    }

}


void WebCam::checkHands(std::vector<cv::Rect> & palm, int rows){


    if ((int)palm.size() > 1){
        if (palm[0].x < palm[1].x){
            if (palm[0].y > palm[1].y){
                //A gauche
                touches[Q] = true;
                touches[D] = false;
            } else {
                touches[Q] = false;
                touches[D] = true;
            }
        } else {
            if (palm[0].y > palm[1].y){
                //A gauche
                touches[Q] = false;
                touches[D] = true;
            } else {
                touches[Q] = true;
                touches[D] = false;
            }
        }
    } else {
        //Dessus dessous
        int dessus = 0;
        int dessous = 0;
        for (int i=0;i<(int)palm.size();i++){
            //Au dessus ou en dessous de la moitié ???
            if (palm[i].y + palm[i].height / 2 < rows / 2){ //Frame.rows
                //Partie supérieure de l'image
                dessus++;
            } else {
                dessous++;
            }
        }
        //Reset
        touches[S] = false;
        touches[Z] = false;

        //Check
        if (dessus > dessous){
            touches[S] = true;
            touches[Z] = false;
        } else  if (dessus < dessous){
            //emit sendKey(Qt::Key_S, true);
            touches[S] = false;
            touches[Z] = true;
        }


        touches[Q] = false;
        //droite gauche
        touches[Q] = false;
        touches[D] = false;
    }
}

WebCam::~WebCam(){
    delete palm_cascade;
    delete fist_cascade;
    delete cap;
    delete timer;
    delete scene;
}
