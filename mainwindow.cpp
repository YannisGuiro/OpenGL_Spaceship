#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StartWindow start;
    start.exec();
    qDebug() << "Nb astéroide:" << start.nb_asteroide;

    this->setFocusPolicy(Qt::TabFocus);
    this->setFixedSize(QSize(1300, 800));



    timer = new QElapsedTimer();
    refresher = new QTimer();
    warning_message = new QTimer();




    ui->gamerender->setAsteroid(start.nb_asteroide);
    ui->frame->setVisible(false);
    ui->warning_hit_label->setVisible(false);

    connect(ui->webcam, SIGNAL(sendKey(int, bool)), this, SLOT(transmitControl(int, bool)));
    connect(ui->gamerender, SIGNAL(end()), this, SLOT(gotEnd()));
    connect(ui->gamerender, SIGNAL(hit()), this, SLOT(gotHit()));
    connect(ui->gamerender, SIGNAL(close()), this, SLOT(close()));
    connect(ui->gamerender, SIGNAL(restart()), this, SLOT(gotRestart()));


    connect(this->refresher, SIGNAL(timeout()), this, SLOT(refreshTimer()));
    connect(this->warning_message, SIGNAL(timeout()), this, SLOT(removeWarningHit()));
    timer->start();
    refresher->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_gamerender_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::removeWarningHit(){
    ui->warning_hit_label->setVisible(false);
}

void MainWindow::refreshTimer(){
    //qDebug() << timer->elapsed();
    int milliseconds = timer->elapsed();
    int seconds      = milliseconds / 1000;
    milliseconds     = milliseconds % 1000;
    int minutes      = seconds / 60;
    seconds          = seconds % 60;
    //qDebug() << minutes << ":" << seconds;
    QString minutes_s = QString::number(minutes);
    QString seconds_s = QString::number(seconds);
    if (minutes_s.size()==1){
        minutes_s = "0" + minutes_s;
    }
    if (seconds_s.size()==1){
        seconds_s = "0" + seconds_s;
    }

    this->ui->timer_display->setText(minutes_s + ":" + seconds_s + "\n" + QString::number(hit) + " hit(s)");

}

void MainWindow::gotHit(){
    hit++;
    ui->warning_hit_label->setVisible(true);
    this->warning_message->start(2000);
}

void MainWindow::gotEnd(){
    ui->frame->setVisible(true);
    ui->label_time->setText("Temps : " + QString::number(timer->elapsed()/1000) + " secondes.");
    ui->label_hit->setText("Nombre touche : " + QString::number(hit) + ".");

}

void MainWindow::gotRestart(){

    // On rend invisible ce qui est inutile
    this->setVisible(false);
    ui->frame->setVisible(false);
    ui->warning_hit_label->setVisible(false);

    // On remets la fenêtre de démarrage
    StartWindow start;
    start.exec();
    qDebug() << "Nb astéroide:" << start.nb_asteroide;

    // On restart le gamerender aussi
    ui->gamerender->setAsteroid(start.nb_asteroide);
    ui->gamerender->reset();

    timer = new QElapsedTimer();
    refresher = new QTimer();
    warning_message = new QTimer();

    timer->start();
    refresher->start(1000);
    hit = 0;
    this->setVisible(true);
}


// Fonction de gestion d'interactions clavier
void MainWindow::keyPressEvent(QKeyEvent * event)
{

    //qDebug() << "Press 1";
    ui->gamerender->keyPressReceiveEvent(event->key());
    event->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
    //qDebug() << "Release 1";
    ui->gamerender->keyReleaseReceiveEvent(event->key());
    event->accept();

}

void MainWindow::transmitControl(int key, bool active){
    if (active){
        ui->gamerender->keyPressReceiveEvent(key);
    } else {
        ui->gamerender->keyReleaseReceiveEvent(key);
    }

}
