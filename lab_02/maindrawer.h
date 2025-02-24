#ifndef MAINDRAWER_H

#define MAINDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QMainWindow>
#include <QPainterPath>
#include <cmath>

#define WIDTH_CANVAS 1200
#define HEIGHT_CANVAS 800
#define CNT_DOTS 10000


double cnt_x_intersection_exp_with_parabola(int mode);
double cnt_y_exp(double x);
double cnt_y_parabola(double x);
double correct_angle(double angle);
void creator_data_exp(double data_x[], double data_y[], double start, double finish, double step, int flag_posi);
void creator_data_parabola(double data_x[], double data_y[], double start, double finish, double step);

class MyDrawWidget : public QWidget
{
    Q_OBJECT

public:
    double transfer_dX = 0, transfer_dY = 0;
    double scale_cX = 0, scale_cY = 0, scale_kX = 1, scale_kY = 1;
    double rotate_cX = 0, rotate_cY = 0, rotate_angle = 0;
    double scale_base = 20;
    int cnt_dots = CNT_DOTS;
    double start_draw = -5, finish_draw = 5, step_draw = (finish_draw - start_draw) / cnt_dots;
    double x_parabola[CNT_DOTS], y_parabola[CNT_DOTS];
    double x_exp_posi[CNT_DOTS], y_exp_posi[CNT_DOTS];
    double x_exp_neg[CNT_DOTS], y_exp_neg[CNT_DOTS];

    void cnt_scale_result(double x, double y, double result[2]);
    void cnt_transfer_result(double x, double y, double result[2]);
    void cnt_rotate_result(double x, double y, double result[2]);
    void cnt_result(double x, double y, double result[2]);
    explicit MyDrawWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;    

};

#endif
