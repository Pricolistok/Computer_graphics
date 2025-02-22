#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QWidget>
#include "ui_mainwindow.h"
#include "maindrawer.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    //public slots:
    //   void reset_draw();

    private:
        Ui::MainWindow *ui;
        MyDrawWidget *drawWidget;
};
#endif // MAINWINDOW_H
