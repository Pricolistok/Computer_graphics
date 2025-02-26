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
#define SCALE 20
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
    double scale_base = SCALE;
    int cnt_dots = CNT_DOTS;
    double start_draw = -5, finish_draw = 5, step_draw = (finish_draw - start_draw) / cnt_dots;
    double x_parabola[CNT_DOTS], y_parabola[CNT_DOTS];
    double x_exp_posi[CNT_DOTS], y_exp_posi[CNT_DOTS];
    double x_exp_neg[CNT_DOTS], y_exp_neg[CNT_DOTS];

    int flag_step_back = 0;

    double transfer_dX_s = 0, transfer_dY_s = 0;
    double scale_cX_s = 0, scale_cY_s = 0, scale_kX_s = 1, scale_kY_s = 1;
    double rotate_cX_s = 0, rotate_cY_s = 0, rotate_angle_s = 0;
    double scale_base_s = 20;
    double x_parabola_s[CNT_DOTS], y_parabola_s[CNT_DOTS];
    double x_exp_posi_s[CNT_DOTS], y_exp_posi_s[CNT_DOTS];
    double x_exp_neg_s[CNT_DOTS], y_exp_neg_s[CNT_DOTS];

    void cnt_scale_result();
    void cnt_transfer_result();
    void cnt_rotate_result();
    void cnt_result(double x, double y, double result[2]);
    explicit MyDrawWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;    

};

#endif
