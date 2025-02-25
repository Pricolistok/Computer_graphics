#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QWidget>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "maindrawer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

void send_error_message(char text[]);
int check_num(const char num[]);
void copy_array(double arr1[], double arr2[]);


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void copy_all_dots();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void reset_transfer();
    void reset_scale();
    void reset_rotate();
    void restart();
    void step_back();


private:
    Ui::MainWindow *ui;
    MyDrawWidget *drawWidget;
};
#endif // MAINWINDOW_H
