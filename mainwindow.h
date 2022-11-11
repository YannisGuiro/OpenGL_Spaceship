#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void on_gamerender_customContextMenuRequested(const QPoint &pos);
    void transmitControl(int key, bool status);
    void refreshTimer();

    void gotHit();
    void gotEnd();
    void gotRestart();
    void removeWarningHit();

private:
    Ui::MainWindow *ui;
    QElapsedTimer *timer;
    QTimer *refresher;
    QTimer *warning_message;
    int hit = 0;
};
#endif // MAINWINDOW_H
