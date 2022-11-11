#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <cstdio>
#include <iostream>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsOpacityEffect>
#include <QGraphicsView>


class WebCam : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WebCam(QWidget *parent = nullptr);
    ~WebCam();

private:
    cv::VideoCapture * cap;
    cv::CascadeClassifier * fist_cascade;
    cv::CascadeClassifier * palm_cascade;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsOpacityEffect *op;
    bool touches_last[5];
    bool touches[5];

    void checkHands(std::vector<cv::Rect> & palm, int rows);


private slots:
    void refresh();

signals:
    void sendKey(int key, bool status);
};

#endif // WEBCAM_H
