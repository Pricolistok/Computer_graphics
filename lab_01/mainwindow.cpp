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
    connect(ui->pushBtnAddDot, SIGNAL(clicked()), this, SLOT(print_text()));
    cout << "hhh" <<endl;
}

void MainWindow::print_text()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(ui->lineEdit_X->text()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(ui->lineEdit_Y->text()));
    cout << ui->lineEdit_X->text().toStdString() << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
