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


class MyDrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyDrawWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
