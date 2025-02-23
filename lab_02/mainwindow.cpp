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
}

int check_num(const char num[])
{
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
    qDebug() << "PPPP";
    QString x_transfer_str = ui->lineEdit_transfer_dX->text();
    QString y_transfer_str = ui->lineEdit_transfer_dY->text();
    char message[100];
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
    qDebug() << "PPPP";
    qDebug() << drawWidget->transfer_dX << "OK";
    qDebug() << drawWidget->transfer_dY;
}

MainWindow::~MainWindow()
{
    delete ui;
}
