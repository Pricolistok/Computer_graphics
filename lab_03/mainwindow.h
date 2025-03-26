#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "maindrawer.h"

#define LEN_TEXT_ERROR_MESSAGE 250

void display_error_message(const char text[LEN_TEXT_ERROR_MESSAGE]);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void draw_line();
    void draw_spector();
    void set_color_line(int id);
    void set_color_BG(int id);
    void set_method(int id);
    void set_free();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyDrawWidget *drawWidget;
    QButtonGroup *radio_btn_group_Line_color;
    QButtonGroup *radio_btn_group_BG_color;
    QButtonGroup *radio_btn_group_method;
};
#endif // MAINWINDOW_H
