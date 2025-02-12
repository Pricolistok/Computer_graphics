#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <QPainter>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushBtnAddDot, SIGNAL(clicked()), this, SLOT(add_row()));
    connect(ui->pushBtnRMall, SIGNAL(clicked()), this, SLOT(clear_table()));
    connect(ui->pushBtnRMDot, SIGNAL(clicked()), this, SLOT(rm_dot()));
}

void MainWindow::add_row()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(ui->lineEdit_X->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(ui->lineEdit_Y->text()));
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
