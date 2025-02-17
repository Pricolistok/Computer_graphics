#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <iostream>
#include <string>
#include <exception>

using namespace std;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background-color:black;");

    drawWidget = new MyDrawWidget(ui->widget);
    drawWidget->setShouldDraw(false);
    drawWidget->mainWindow = this;
    drawWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());  // Устанавливаем его размер
    drawWidget->show();

    connect(ui->pushBtnAddDot, SIGNAL(clicked()), this, SLOT(add_row()));
    connect(ui->pushBtnRMall, SIGNAL(clicked()), this, SLOT(clear_table()));
    connect(ui->pushBtnFind, SIGNAL(clicked()), this, SLOT(reset_draw()));
}

int check_num(string num)
{
    try
    {
        stoi(num);
        return 0;
    }
    catch (exception)
    {
        return 1;
    }
}

void send_error_message(string text)
{
    QMessageBox message;
    message.setWindowTitle("Error");
    message.setText(text.c_str());
    message.exec();
}

void MyDrawWidget::setShouldDraw(bool value)
{
    flag_draw = value;
}


void MainWindow::reset_draw()
{
    QString data;
    char buffer[100];
    int result_message;
    string str_mes;
    drawWidget->setShouldDraw(true);
    ui->widget->update();
    int cnt_dots = ui->tableWidget->rowCount();
    cout << cnt_dots << endl;
    for (int i = 0; i < cnt_dots; i++)
    {
        data = ui->tableWidget->item(i, 0)->text();
        if (check_num(data.toStdString()) != 0)
        {
            result_message = snprintf(buffer, 100, "Error with X in row %d", i);
            str_mes = buffer;
            send_error_message(str_mes);
            return;
        }
        data = ui->tableWidget->item(i, 1)->text();
        if (check_num(data.toStdString()) != 0)
        {
            result_message = snprintf(buffer, 100, "Error with Y in row %d", i);
            str_mes = buffer;
            send_error_message(str_mes);
            return;
        }
        drawWidget->x_data.push_back(ui->tableWidget->item(i, 0)->text().toInt());
        drawWidget->y_data.push_back(ui->tableWidget->item(i, 1)->text().toInt());
        cout << i << " " << ui->tableWidget->item(i, 0)->text().toStdString() << " " << ui->tableWidget->item(i, 1)->text().toStdString() << endl;
    }
}

void MainWindow::add_row()
{
    QString x_position_str = ui->lineEdit_X->text();
    QString y_position_str = ui->lineEdit_Y->text();
    if (check_num(x_position_str.toStdString()) != 0)
    {
        send_error_message("Error with X");
        return;
    }
    if (check_num(y_position_str.toStdString()) != 0)
    {
        send_error_message("Error with Y");
        return;
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(x_position_str));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(y_position_str));
}

void MainWindow::clear_table()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::rm_dot()
{
    QString input_data = ui->lineEditRMId->text();
    if (check_num(input_data.toStdString()) != 0)
    {
        send_error_message("Error with input data");
        return;
    }
    if (input_data.toInt() > ui->tableWidget->rowCount() - 1 || input_data.toInt() <= 0)
    {
        send_error_message("Error with index of row");
        return;
    }
    ui->tableWidget->removeRow(ui->lineEditRMId->text().toInt() - 1);
}

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: black;");
}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen({Qt::white, 2});
    painter.drawLine(0, 300, 1000, 300);
    painter.drawLine(990, 295, 1000, 300);
    painter.drawLine(990, 305, 1000, 300);
    painter.drawLine(500, 0, 500, 600);
    painter.drawLine(495, 10, 500, 0);
    painter.drawLine(505, 10, 500, 0);
    painter.setPen({Qt::red, 2});
    for (int i = 0; i < int(this->x_data.size()); i++)
    {
        painter.drawEllipse(QPoint(this->x_data[i] + 500, -1 * this->y_data[i] + 300), 1, 1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
