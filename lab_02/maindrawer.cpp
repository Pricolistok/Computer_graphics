#include "maindrawer.h"


MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{
    creator_data_parabola(x_parabola, y_parabola, start_draw + 3, finish_draw - 3, step_draw);
    creator_data_exp(x_exp_posi, y_exp_posi, start_draw, finish_draw - 4, step_draw, 1);
    creator_data_exp(x_exp_neg, y_exp_neg, start_draw + 4, finish_draw, step_draw, -1);
}

void creator_data_parabola(double data_x[], double data_y[], double start, double finish, double step)
{
    int iter = 0;
    for (double x = start; x <= finish; x += step)
    {
        data_x[iter] = x * SCALE;
        data_y[iter] = cnt_y_parabola(x) * SCALE;
        iter++;
    }
}

void creator_data_exp(double data_x[], double data_y[], double start, double finish, double step, int flag_posi)
{
    int iter = 0;
    for (double x = start; x <= finish; x += step)
    {
        data_x[iter] = x * SCALE;
        data_y[iter] = cnt_y_exp(flag_posi * x) * SCALE;
        iter++;
    }
}


void MyDrawWidget::cnt_transfer_result()
{
    for (int i = 0; i < CNT_DOTS; i++)
    {
        this->x_parabola[i] = this->transfer_dX + this->x_parabola[i];
        this->y_parabola[i] = this->y_parabola[i] -  this->transfer_dY;

        this->x_exp_posi[i] = this->transfer_dX + this->x_exp_posi[i];
        this->y_exp_posi[i] = this->y_exp_posi[i] -  this->transfer_dY;

        this->x_exp_neg[i] = this->transfer_dX + this->x_exp_neg[i];
        this->y_exp_neg[i] = this->y_exp_neg[i] -  this->transfer_dY;
    }
}


void MyDrawWidget::cnt_rotate_result()
{
    for (int i = 0; i < CNT_DOTS; i++)
    {
        this->x_parabola[i] = this->rotate_cX + ((this->x_parabola[i] - this->rotate_cX) * cos(this->rotate_angle)) + ((this->y_parabola[i] - this->rotate_cY) * sin(this->rotate_angle) * 1200/800);
        this->y_parabola[i] = this->rotate_cY + ((this->y_parabola[i] - this->rotate_cY) * cos(this->rotate_angle)) - ((this->x_parabola[i] - this->rotate_cX) * sin(this->rotate_angle) * 800/1200);

        this->x_exp_posi[i] = this->rotate_cX + ((this->x_exp_posi[i] - this->rotate_cX) * cos(this->rotate_angle)) + ((this->y_exp_posi[i] - this->rotate_cY) * sin(this->rotate_angle) * 1200/800);
        this->y_exp_posi[i] = this->rotate_cY + ((this->y_exp_posi[i] - this->rotate_cY) * cos(this->rotate_angle)) - ((this->x_exp_posi[i] - this->rotate_cX) * sin(this->rotate_angle) * 800/1200);

        this->x_exp_neg[i] = this->rotate_cX + ((this->x_exp_neg[i] - this->rotate_cX) * cos(this->rotate_angle)) + ((this->y_exp_neg[i] - this->rotate_cY) * sin(this->rotate_angle) * 1200/800);
        this->y_exp_neg[i] = this->rotate_cY + ((this->y_exp_neg[i] - this->rotate_cY) * cos(this->rotate_angle)) - ((this->x_exp_neg[i] - this->rotate_cX) * sin(this->rotate_angle) * 800/1200);

    }
}


void MyDrawWidget::cnt_scale_result()
{
    for (int i = 0; i < CNT_DOTS; i++)
    {
        this->x_parabola[i] = (this->scale_kX * this->x_parabola[i]) + this->scale_cX * (1 - this->scale_kX);
        this->y_parabola[i] = (this->scale_kY * this->y_parabola[i]) + this->scale_cY * (1 - this->scale_kY);

        this->x_exp_posi[i] = (this->scale_kX * this->x_exp_posi[i]) + this->scale_cX * (1 - this->scale_kX);
        this->y_exp_posi[i] = (this->scale_kY * this->y_exp_posi[i]) + this->scale_cY * (1 - this->scale_kY);

        this->x_exp_neg[i] = (this->scale_kX * this->x_exp_neg[i]) + this->scale_cX * (1 - this->scale_kX);
        this->y_exp_neg[i] = (this->scale_kY * this->y_exp_neg[i]) + this->scale_cY * (1 - this->scale_kY);
    }
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
        painter.drawEllipse(QPointF(x_parabola[i] + offset_to_center_x, y_parabola[i] + offset_to_center_y), 1, 1);
        painter.drawEllipse(QPointF(x_exp_posi[i] + offset_to_center_x, y_exp_posi[i] + offset_to_center_y), 1, 1);
        painter.drawEllipse(QPointF(x_exp_neg[i] + offset_to_center_x, y_exp_neg[i] + offset_to_center_y), 1, 1);
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
