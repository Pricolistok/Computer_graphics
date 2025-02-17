#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;

int check_num(string num);
void send_error_message(string text);
double cnt_bisector(double a, double b, double c);
double cnt_size_of_line(int x_data_1, int x_data_2, int y_data_1, int y_data_2);
void message_result(int arr_result[], double tmp);
int cnt_y_bis(double a, double b, int y1, int y2);
int cnt_x_bis(double a, double b, int x1, int x2);
int cnt_scale(int arr_result[], int len, int screen_width, int screen_height);
bool line_intersection(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int* intersection_x, int* intersection_y);
bool are_points_distinct(int x1, int y1, int x2, int y2, int x3, int y3);


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MyDrawWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MyDrawWidget(QWidget *parent = nullptr);
        QMainWindow *mainWindow;
        int flag_draw = 0;
        void setShouldDraw(bool value);
        vector<int> x_data;
        vector<int> y_data;
        int flag_cnt = 0;
        void analisys_dots(int arr_result[10]);

    protected:
        void paintEvent(QPaintEvent *event) override;
};


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
    void reset_draw();

private:
    Ui::MainWindow *ui;
    MyDrawWidget *drawWidget;
};
#endif // MAINWINDOW_H
