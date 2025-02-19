#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;

int check_num(QString num);
void send_error_message(string text);
double cnt_bisector(double a, double b, double c);
double cnt_size_of_line(double x_data_1, double x_data_2, double y_data_1, double y_data_2);
void message_result(double arr_result[]);
double cnt_y_bis(double a, double b, double y1, double y2);
double cnt_x_bis(double a, double b, double x1, double x2);
double cnt_scale(double arr_result[], int len, int screen_width, int screen_height);
void line_intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double* intersection_x, double* intersection_y);
bool are_points_distinct(double x1, double y1, double x2, double y2, double x3, double y3);
void set_data(double arr_result[], double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double b, double c);
void findCanonicalParams(double x1, double y1, double x2, double y2, double arr_res[]);


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
        vector<double> x_data;
        vector<double> y_data;
        int flag_cnt = 0;
        void analisys_dots(double arr_result[11]);

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
