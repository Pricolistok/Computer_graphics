#include "maindrawer.h"

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

double cnt_y_parabola(double x)
{
    return pow(x, 2) * -1;
}

double cnt_y_exp(double x)
{
    return exp(x) * -1;
}

double cnt_x_intersection_exp_with_parabola(int mode)
{
    double result;
    for (double x = -10; x <= 10; x += 0.0001)
    {
        if (fabs(cnt_y_exp(x * mode) - cnt_y_parabola(x)) <= 1e-3)
        {
            result = x;
            break;
        }

    }
    return result;
}

double cnt_x_intersection_exp_with_exp()
{
    double result;
    for (double x = -10; x <= 10; x += 0.0001)
    {
        if (cnt_y_exp(-x) - cnt_y_exp(x) <= 1e-6)
            result = x;
    }
    return result;
}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    double offset_to_center_x = WIDTH_CANVAS / 2, offset_to_center_y = HEIGHT_CANVAS / 2;
    double scale = 30;
    QPainter painter(this);
    QBrush brush(Qt::red, Qt::BDiagPattern);
    QPainterPath path;
    Q_UNUSED(event);
    double result_x_exp_1_parabola = cnt_x_intersection_exp_with_parabola(1);
    double result_x_exp_2_parabola = cnt_x_intersection_exp_with_parabola(-1);
    double result_x_exp_exp = cnt_x_intersection_exp_with_exp();

    painter.setPen(Qt::white);
    painter.drawLine(500, 0, 500, 600);

    for (double x = -10; x <= 10; x += 0.01)
    {
        painter.drawEllipse(QPointF(x * scale + offset_to_center_x, cnt_y_parabola(x) * scale + offset_to_center_y), 1, 0);
        painter.drawEllipse(QPointF(x * scale + offset_to_center_x, cnt_y_exp(x) * scale + offset_to_center_y), 1, 0);
        painter.drawEllipse(QPointF(x * scale + offset_to_center_x, cnt_y_exp(-x) * scale + offset_to_center_y), 1, 0);
    }

    path.moveTo(result_x_exp_1_parabola * scale + offset_to_center_x, cnt_y_parabola(result_x_exp_1_parabola) * scale + offset_to_center_y);

    for (double x = result_x_exp_1_parabola; x <= result_x_exp_2_parabola; x += 0.01)
        path.lineTo(x * scale + offset_to_center_x, cnt_y_parabola(x) * scale + offset_to_center_y);

    for (double x = result_x_exp_2_parabola; x >= result_x_exp_exp; x -= 0.01)
        path.lineTo(x * scale + offset_to_center_x, cnt_y_exp(-x) * scale + offset_to_center_y);

    for (double x = result_x_exp_exp; x >= result_x_exp_1_parabola; x -= 0.01)
        path.lineTo(x * scale + offset_to_center_x, cnt_y_exp(x) * scale + offset_to_center_y);

    path.closeSubpath();

    painter.setPen(QPen(Qt::black));
    painter.setBrush(brush);
    // painter.setBrush(QBrush(Qt::red));

    painter.drawPath(path);

}
