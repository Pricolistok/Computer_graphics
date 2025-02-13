#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
using namespace std;

int check_num(string num);
void send_error_message(string text);

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

public slots:
    void add_row();
    void clear_table();
    void rm_dot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
