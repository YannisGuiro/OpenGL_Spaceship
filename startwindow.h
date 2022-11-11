#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    int nb_asteroide = 1;

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
