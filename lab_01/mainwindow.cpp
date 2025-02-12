#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushBtnAddDot, SIGNAL(clicked()), this, SLOT(add_row()));
    connect(ui->pushBtnRMall, SIGNAL(clicked()), this, SLOT(clear_table()));
    connect(ui->pushBtnRMDot, SIGNAL(clicked()), this, SLOT(rm_dot()));
}

int MainWindow::check_num(string num)
{
    for (size_t i = 0; i < num.size(); i++)
    {
        if (isdigit(num[i]) != true)
        {
            return 1;
        }
    }
    return 0;
}

void MainWindow::add_row()
{
    QMessageBox message;
    QString x_position_str = ui->lineEdit_X->text();
    QString y_position_str = ui->lineEdit_Y->text();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    if (check_num(x_position_str.toStdString()) != 0)
    {
        message.setWindowTitle("Error");
        message.setText("Error with X");
        message.exec();
        return;
    }
    if (check_num(y_position_str.toStdString()) != 0)
    {
        message.setInformativeText("Error");
        message.setText("Error with Y");
        message.exec();
        return;
    }
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
    ui->tableWidget->removeRow(ui->lineEditRMId->text().toInt() - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
