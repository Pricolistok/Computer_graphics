#include "mainwindow.h"


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
}

int check_num(const char num[])
{
    size_t len_num = strlen(num);
    if (len_num == 0)
        return false;
    for (size_t i = 0; i < strlen(num); i++)
    {
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
    drawWidget->transfer_dX = x_transfer_str.toDouble();
    drawWidget->transfer_dY = y_transfer_str.toDouble();
    drawWidget->update();
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
    drawWidget->scale_cX = scale_cX_str.toDouble() + WIDTH_CANVAS / 2;
    drawWidget->scale_cY = scale_cY_str.toDouble() + HEIGHT_CANVAS / 2;
    drawWidget->scale_kX = scale_kX_str.toDouble();
    drawWidget->scale_kY = scale_kY_str.toDouble();
    drawWidget->update();
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
    drawWidget->rotate_cX = rotate_cX_str.toDouble() + WIDTH_CANVAS / 2;
    drawWidget->rotate_cY = rotate_cY_str.toDouble() + HEIGHT_CANVAS / 2;
    drawWidget->rotate_angle = correct_angle(rotate_angle_str.toDouble());
    drawWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
