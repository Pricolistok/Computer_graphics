#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(print_text()));
}

void MainWindow::print_text()
{
    QMessageBox msgBox;
    msgBox.setText("Hello");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
