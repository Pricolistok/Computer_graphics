#ifndef MAINDRAWER_H

#define MAINDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QMainWindow>
#include <QPainterPath>
#include <cmath>

#define WIDTH_CANVAS 1000
#define HEIGHT_CANVAS 600

double cnt_x_intersection_exp_with_parabola(int mode);
double cnt_y_exp(double x);
double cnt_y_parabola(double x);
double correct_angle(double angle);


class MyDrawWidget : public QWidget
{
    Q_OBJECT

public:
    double transfer_dX = 0, transfer_dY = 0;
    double scale_cX = 0, scale_cY = 0;
    double scale_kX = 1, scale_kY = 1;
    double rotate_cX = 0, rotate_cY = 0;
    double rotate_angle = 0;
    explicit MyDrawWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
