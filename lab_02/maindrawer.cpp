#include "maindrawer.h"


MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{
    creator_data_parabola(x_parabola, y_parabola, start_draw - 3, finish_draw + 3, step_draw);
    creator_data_exp(x_exp_posi, y_exp_posi, start_draw, finish_draw - 4, step_draw, 1);
    creator_data_exp(x_exp_neg, y_exp_neg, start_draw + 4, finish_draw, step_draw, -1);
}

void creator_data_parabola(double data_x[], double data_y[], double start, double finish, double step)
{
    int iter = 0;
    for (double x = start; x <= finish; x += step)
    {
        data_x[iter] = x;
        data_y[iter] = cnt_y_parabola(x);
        iter++;
    }
}

void creator_data_exp(double data_x[], double data_y[], double start, double finish, double step, int flag_posi)
{
    int iter = 0;
    for (double x = start; x <= finish; x += step)
    {
        data_x[iter] = x;
        data_y[iter] = cnt_y_exp(flag_posi * x);
        iter++;
    }
}


void MyDrawWidget::cnt_transfer_result(double x, double y, double result[2])
{
    result[0] = this->transfer_dX + x;
    result[1] = y -  this->transfer_dY;
}


void MyDrawWidget::cnt_rotate_result(double x, double y, double result[2])
{
    result[0] = this->rotate_cX + ((x - this->rotate_cX) * cos(this->rotate_angle)) + ((y - this->rotate_cY) * sin(this->rotate_angle) * 1200/800);
    result[1] = this->rotate_cY + ((y - this->rotate_cY) * cos(this->rotate_angle)) - ((x - this->rotate_cX) * sin(this->rotate_angle) * 800/1200);
}


void MyDrawWidget::cnt_scale_result(double x, double y, double result[2])
{
    result[0] = (this->scale_kX * x) + this->scale_cX * (1 - this->scale_kX);
    result[1] = (this->scale_kY * y) + this->scale_cY * (1 - this->scale_kY);
}

void MyDrawWidget::cnt_result(double x, double y, double result[2])
{
    double x_now, y_now;
    cnt_transfer_result(x, y, result);
    x_now = result[0];
    y_now = result[1];

    cnt_scale_result(x_now, y_now, result);
    x_now = result[0];
    y_now = result[1];

    cnt_rotate_result(x_now, y_now, result);
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
    QPainter painter(this);
    double result_now[2];
    QBrush brush(Qt::red, Qt::BDiagPattern);
    QPainterPath path;
    Q_UNUSED(event);
    // double result_x_exp_1_parabola = cnt_x_intersection_exp_with_parabola(1);
    // double result_x_exp_2_parabola = cnt_x_intersection_exp_with_parabola(-1);
    // double result_x_exp_exp = cnt_x_intersection_exp_with_exp();

    painter.setPen(Qt::white);

    for (int i = 0; i < this->cnt_dots; i++)
    {
        cnt_result(this->x_parabola[i], this->y_parabola[i], result_now);
        x_parabola[i] = result_now[0];
        y_parabola[i] = result_now[1];
        painter.drawEllipse(QPointF(result_now[0] * this->scale_base + offset_to_center_x, result_now[1] * this->scale_base + offset_to_center_y), 1, 1);

        cnt_result(this->x_exp_posi[i], this->y_exp_posi[i], result_now);
        x_exp_posi[i] = result_now[0];
        y_exp_posi[i] = result_now[1];
        painter.drawEllipse(QPointF(result_now[0] * this->scale_base + offset_to_center_x, result_now[1] * this->scale_base + offset_to_center_y), 1, 1);

        cnt_result(this->x_exp_neg[i], this->y_exp_neg[i], result_now);
        x_exp_neg[i] = result_now[0];
        y_exp_neg[i] = result_now[1];
        painter.drawEllipse(QPointF(result_now[0] * this->scale_base + offset_to_center_x, result_now[1] * this->scale_base + offset_to_center_y), 1, 1);
    }

    // path.moveTo(result_x_exp_1_parabola * scale + offset_to_center_x, cnt_y_parabola(result_x_exp_1_parabola) * scale + offset_to_center_y);

    // for (double x = result_x_exp_1_parabola; x <= result_x_exp_2_parabola; x += 0.01)
    //     path.lineTo(x * scale + offset_to_center_x, cnt_y_parabola(x) * scale + offset_to_center_y);

    // for (double x = result_x_exp_2_parabola; x >= result_x_exp_exp; x -= 0.01)
    //     path.lineTo(x * scale + offset_to_center_x, cnt_y_exp(-x) * scale + offset_to_center_y);

    // for (double x = result_x_exp_exp; x >= result_x_exp_1_parabola; x -= 0.01)
    //     path.lineTo(x * scale + offset_to_center_x, cnt_y_exp(x) * scale + offset_to_center_y);

    path.closeSubpath();

    painter.setPen(QPen(Qt::black));
    painter.setBrush(brush);
    // painter.setBrush(QBrush(Qt::red));

    painter.drawPath(path);

}
