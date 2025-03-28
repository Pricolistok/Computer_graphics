#include "maindrawer.h"


MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{
    int len = 0;
    creator_data_parabola(x_parabola, y_parabola, start_draw + 3, finish_draw - 3, step_draw);
    creator_data_exp(x_exp_posi, y_exp_posi, start_draw, finish_draw - 4, step_draw, 1);
    creator_data_exp(x_exp_neg, y_exp_neg, start_draw + 4, finish_draw, step_draw, -1);
    creator_data_hatching(x_hatching, y_hatching, &len);
    len_hatching = len;

}

void creator_data_hatching(double data_x[], double data_y[], int *len_data)
{
    double result_x_exp_1_parabola = cnt_x_intersection_exp_with_parabola(1);
    double result_x_exp_2_parabola = cnt_x_intersection_exp_with_parabola(-1);
    double result_x_exp_exp = cnt_x_intersection_exp_with_exp();
    int iter = 0;
    for (double x = result_x_exp_1_parabola; x <= result_x_exp_2_parabola; x += 0.01)
    {
        data_x[iter] = x * SCALE;
        data_y[iter] =  cnt_y_parabola(x) * SCALE;
        iter++;
    }
    for (double x = result_x_exp_2_parabola; x >= result_x_exp_exp; x -= 0.01)
    {
        data_x[iter] = x * SCALE;
        data_y[iter] =  cnt_y_exp(-x) * SCALE;
        iter++;
    }
    for (double x = result_x_exp_exp; x >= result_x_exp_1_parabola; x -= 0.01)
    {
        data_x[iter] = x * SCALE;
        data_y[iter] =  cnt_y_exp(x) * SCALE;
        iter++;
    }
    *len_data = iter;
}

void creator_data_parabola(double data_x[], double data_y[], double start, double finish, double step)
{
    int iter = 0;
    for (int i = 0; i < CNT_DOTS; i++)
    {
        data_x[i] = NULL;
        data_y[i] = NULL;
    }
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
    for (int i = 0; i < CNT_DOTS; i++)
    {
        data_x[i] = NULL;
        data_y[i] = NULL;
    }
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
    for (int i = 0; i < len_hatching; i++)
    {
        this->x_hatching[i] = this->transfer_dX + this->x_hatching[i];
        this->y_hatching[i] = this->y_hatching[i] -  this->transfer_dY;
    }
}

void MyDrawWidget::cnt_rotate_result()
{
    double temp_x, temp_y;
    double new_angle = -this->rotate_angle * M_PI / 180;
    for (int i = 0; i < CNT_DOTS; i++)
    {
        temp_x = this->x_parabola[i];
        temp_y = this->y_parabola[i];
        this->x_parabola[i] = this->rotate_cX + ((temp_x - this->rotate_cX) * cos(new_angle)) - ((temp_y - this->rotate_cY) * sin(new_angle));
        this->y_parabola[i] = this->rotate_cY + ((temp_x - this->rotate_cX) * sin(new_angle)) + ((temp_y - this->rotate_cY) * cos(new_angle));

        temp_x = this->x_exp_posi[i];
        temp_y = this->y_exp_posi[i];
        this->x_exp_posi[i] = this->rotate_cX + ((temp_x - this->rotate_cX) * cos(new_angle)) - ((temp_y - this->rotate_cY) * sin(new_angle));
        this->y_exp_posi[i] = this->rotate_cY + ((temp_x - this->rotate_cX) * sin(new_angle)) + ((temp_y - this->rotate_cY) * cos(new_angle));

        temp_x = this->x_exp_neg[i];
        temp_y = this->y_exp_neg[i];
        this->x_exp_neg[i] = this->rotate_cX + ((temp_x - this->rotate_cX) * cos(new_angle)) - ((temp_y - this->rotate_cY) * sin(new_angle));
        this->y_exp_neg[i] = this->rotate_cY + ((temp_x - this->rotate_cX) * sin(new_angle)) + ((temp_y - this->rotate_cY) * cos(new_angle));
    }
    for (int i = 0; i < len_hatching; i++)
    {
        temp_x = this->x_hatching[i];
        temp_y = this->y_hatching[i];
        this->x_hatching[i] = this->rotate_cX + ((temp_x - this->rotate_cX) * cos(new_angle)) - ((temp_y - this->rotate_cY) * sin(new_angle));
        this->y_hatching[i] = this->rotate_cY + ((temp_x - this->rotate_cX) * sin(new_angle)) + ((temp_y - this->rotate_cY) * cos(new_angle));
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
    for (int i = 0; i < len_hatching; i++)
    {
        this->x_hatching[i] = (this->scale_kX * this->x_hatching[i]) + this->scale_cX * (1 - this->scale_kX);
        this->y_hatching[i] = (this->scale_kY * this->y_hatching[i]) + this->scale_cY * (1 - this->scale_kY);
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

    painter.setPen(Qt::white);


    for (int i = 0; i < this->cnt_dots; i++)
    {
        painter.drawEllipse(QPointF(x_parabola[i] + offset_to_center_x, y_parabola[i] + offset_to_center_y), 1, 1);
        painter.drawEllipse(QPointF(x_exp_posi[i] + offset_to_center_x, y_exp_posi[i] + offset_to_center_y), 1, 1);
        painter.drawEllipse(QPointF(x_exp_neg[i] + offset_to_center_x, y_exp_neg[i] + offset_to_center_y), 1, 1);
    }

    path.moveTo(x_hatching[0] + offset_to_center_x, y_hatching[0] + offset_to_center_y);
    x_hatching[len_hatching - 1] = x_hatching[0];
    y_hatching[len_hatching - 1] = y_hatching[0];
    painter.setPen(Qt::red);
    for (int i = 0; i < len_hatching; i++)
    {
        painter.drawEllipse(QPointF(x_hatching[i] + offset_to_center_x, y_hatching[i] + offset_to_center_y), 1, 1);
        qDebug() << x_hatching[i] + offset_to_center_x << " " << y_hatching[i] + offset_to_center_y;
        path.lineTo(x_hatching[i] + offset_to_center_x, y_hatching[i] + offset_to_center_y);
    }

    path.closeSubpath();
    painter.setBrush(brush);
    painter.drawPath(path);

}
