#include "mainwindow.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background-color:black;");

    drawWidget = new MyDrawWidget(ui->widget);
    drawWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    drawWidget->show();
    drawWidget->update();

    connect(ui->pushBtnFind, SIGNAL(clicked()), this, SLOT(reset_draw()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
