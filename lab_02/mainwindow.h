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


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void reset_transfer();

private:
    Ui::MainWindow *ui;
    MyDrawWidget *drawWidget;
};
#endif // MAINWINDOW_H
