#include "mainwindow.h"

void copy_array(double arr1[], double arr2[])
{
    for (int i = 0; i < CNT_DOTS; i++)
        arr1[i] = arr2[i];
}


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet("background-color:black;");
    drawWidget = new MyDrawWidget(ui->widget);
    drawWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    drawWidget->show();
    drawWidget->update();
    connect(ui->pushButton_transfer, SIGNAL(clicked()), this, SLOT(reset_transfer()));
    connect(ui->pushButton_scale, SIGNAL(clicked()), this, SLOT(reset_scale()));
    connect(ui->pushButton_rotate, SIGNAL(clicked()), this, SLOT(reset_rotate()));
    connect(ui->pushButton_restart, SIGNAL(clicked()), this, SLOT(restart()));
    connect(ui->pushButton_step_back, SIGNAL(clicked()), this, SLOT(step_back()));
}

void MainWindow::step_back()
{
    drawWidget->flag_step_back = 1;
    drawWidget->transfer_dX = drawWidget->transfer_dX_s;
    drawWidget->transfer_dY = drawWidget->transfer_dY_s;

    drawWidget->scale_cX = drawWidget->scale_cX_s;
    drawWidget->scale_cY = drawWidget->scale_cY_s;
    drawWidget->scale_kX = drawWidget->scale_kX_s;
    drawWidget->scale_kY = drawWidget->scale_kY_s;

    drawWidget->rotate_angle = drawWidget->rotate_angle_s;
    drawWidget->rotate_cX = drawWidget->rotate_cX;
    drawWidget->rotate_cY = drawWidget->rotate_cY;


    copy_array(drawWidget->x_parabola, drawWidget->x_parabola_s);
    copy_array(drawWidget->y_parabola, drawWidget->y_parabola_s);

    copy_array(drawWidget->x_exp_posi, drawWidget->x_exp_posi_s);
    copy_array(drawWidget->y_exp_posi, drawWidget->y_exp_posi_s);

    copy_array(drawWidget->x_exp_neg, drawWidget->x_exp_neg_s);
    copy_array(drawWidget->y_exp_neg, drawWidget->y_exp_neg_s);

    drawWidget->update();

}

void MainWindow::copy_all_dots()
{
    copy_array(drawWidget->x_parabola_s, drawWidget->x_parabola);
    copy_array(drawWidget->y_parabola_s, drawWidget->y_parabola);

    copy_array(drawWidget->x_exp_posi_s, drawWidget->x_exp_posi);
    copy_array(drawWidget->y_exp_posi_s, drawWidget->y_exp_posi);

    copy_array(drawWidget->x_exp_neg_s, drawWidget->x_exp_neg);
    copy_array(drawWidget->y_exp_neg_s, drawWidget->y_exp_neg);
}

int check_num(const char num[])
{
    int flag_dot = 0;
    size_t len_num = strlen(num);
    if (len_num == 0)
        return false;
    for (size_t i = 0; i < strlen(num); i++)
    {
        if (num[i] == '.' && flag_dot == 0)
        {
            flag_dot = 1;
            continue;
        }
        else if (num[i] == '.' && flag_dot == 1)
            return false;
        if (i == 0 && (num[i] == '+' || num[i] == '-'))
            continue;            
        if (isdigit(num[i]) != true)
            return false;
    }
    return true;
}

void send_error_message(char text[])
{
    QMessageBox message;
    message.setWindowTitle("Ошибка!");
    message.setText(text);
    message.exec();
}


void MainWindow::reset_transfer()
{
    QString x_transfer_str = ui->lineEdit_transfer_dX->text();
    QString y_transfer_str = ui->lineEdit_transfer_dY->text();
    char message[150];
    if (!check_num(x_transfer_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение переноса по X!");
        send_error_message(message);
        return;
    }
    if (!check_num(y_transfer_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение переноса по Y!");
        send_error_message(message);
        return;
    }
    drawWidget->transfer_dX_s = drawWidget->transfer_dX;
    drawWidget->transfer_dY_s = drawWidget->transfer_dY_s;
    copy_all_dots();

    drawWidget->transfer_dX = x_transfer_str.toDouble();
    drawWidget->transfer_dY = y_transfer_str.toDouble();
    drawWidget->cnt_transfer_result();
    drawWidget->update();
    drawWidget->flag_step_back = 0;
}


void MainWindow::reset_scale()
{
    QString scale_cX_str = ui->lineEdit_scale_cX->text();
    QString scale_cY_str = ui->lineEdit_scale_cY->text();
    QString scale_kX_str = ui->lineEdit_scale_kX->text();
    QString scale_kY_str = ui->lineEdit_scale_kY->text();
    char message[150];
    if (!check_num(scale_cX_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение координат центра по X!");
        send_error_message(message);
        return;
    }
    if (!check_num(scale_cY_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение координат центра по Y!");
        send_error_message(message);
        return;
    }
    if (!check_num(scale_kX_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение коэффициента масштабирования по X!");
        send_error_message(message);
        return;
    }
    if (!check_num(scale_kY_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение коэффициента масштабирования по Y!");
        send_error_message(message);
        return;
    }

    drawWidget->scale_cX_s = drawWidget->scale_cX;
    drawWidget->scale_cY_s = drawWidget->scale_cY;
    drawWidget->scale_kX_s = drawWidget->scale_kX;
    drawWidget->scale_kY_s = drawWidget->scale_kY;
    copy_all_dots();

    drawWidget->scale_cX = scale_cX_str.toDouble();
    drawWidget->scale_cY = scale_cY_str.toDouble();
    drawWidget->scale_kX = scale_kX_str.toDouble();
    drawWidget->scale_kY = scale_kY_str.toDouble();
    drawWidget->cnt_scale_result();
    drawWidget->update();
    drawWidget->flag_step_back = 0;
}

double correct_angle(double angle)
{
    int flag = 1;
    if (angle < 0)
    {
        flag = -1;
        angle *= -1;
    }

    while (angle > 360)
        angle -= 360;

    return angle * flag;
}


void MainWindow::reset_rotate()
{
    QString rotate_cX_str = ui->lineEdit_rotate_cX->text();
    QString rotate_cY_str = ui->lineEdit_rotate_cY->text();
    QString rotate_angle_str = ui->lineEdit_rotate_angle->text();
    char message[150];
    if (!check_num(rotate_cX_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение координат центра по X!");
        send_error_message(message);
        return;
    }
    if (!check_num(rotate_cY_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение координат центра по Y!");
        send_error_message(message);
        return;
    }
    if (!check_num(rotate_angle_str.toStdString().c_str()))
    {
        strcpy_s(message, "Ошибка! Ошибка при введение угла поворота!");
        send_error_message(message);
        return;
    }

    drawWidget->rotate_angle_s = drawWidget->rotate_angle;
    drawWidget->rotate_cX_s = drawWidget->rotate_cX;
    drawWidget->rotate_cY_s = drawWidget->rotate_cY;
    copy_all_dots();

    drawWidget->rotate_cX = rotate_cX_str.toDouble();
    drawWidget->rotate_cY = rotate_cY_str.toDouble();
    drawWidget->rotate_angle = correct_angle(rotate_angle_str.toDouble());
    drawWidget->cnt_rotate_result();
    drawWidget->update();
    drawWidget->flag_step_back = 0;
}

void MainWindow::restart()
{
    drawWidget->transfer_dX_s = drawWidget->transfer_dX;
    drawWidget->transfer_dY_s = drawWidget->transfer_dY;
    drawWidget->scale_cX_s = drawWidget->scale_cX;
    drawWidget->scale_cY_s = drawWidget->scale_cY;
    drawWidget->scale_kX_s = drawWidget->scale_kX;
    drawWidget->scale_kY_s = drawWidget->scale_kY;
    drawWidget->rotate_angle_s = drawWidget->rotate_angle;
    drawWidget->rotate_cX_s = drawWidget->rotate_cX;
    drawWidget->rotate_cY_s = drawWidget->rotate_cY;
    copy_all_dots();

    creator_data_parabola(drawWidget->x_parabola, drawWidget->y_parabola, drawWidget->start_draw + 3, drawWidget->finish_draw - 3, drawWidget->step_draw);
    creator_data_exp(drawWidget->x_exp_posi, drawWidget->y_exp_posi, drawWidget->start_draw, drawWidget->finish_draw - 4, drawWidget->step_draw, 1);
    creator_data_exp(drawWidget->x_exp_neg, drawWidget->y_exp_neg, drawWidget->start_draw + 4, drawWidget->finish_draw, drawWidget->step_draw, -1);

    drawWidget->transfer_dX = 0;
    drawWidget->transfer_dY = 0;
    drawWidget->scale_cX = 0;
    drawWidget->scale_cY = 0;
    drawWidget->scale_kX = 1;
    drawWidget->scale_kY = 1;
    drawWidget->rotate_cX = 0;
    drawWidget->rotate_cY = 0;
    drawWidget->rotate_angle = 0;
    drawWidget->flag_step_back = 0;
    drawWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
