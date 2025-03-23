#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet("background-color:black;");
    drawWidget = new MyDrawWidget(ui->widget);
    drawWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    drawWidget->show();
    drawWidget->update();

    radio_btn_group_BG_color = new QButtonGroup(this);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgDarkBlue, 1);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgDarkGreen, 2);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgLightBlue, 3);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgLightGreen, 4);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgOrange, 5);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgRed, 6);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgViolet, 7);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgWhite, 8);
    radio_btn_group_BG_color->addButton(ui->radioButtonBgYellow, 9);

    radio_btn_group_Line_color = new QButtonGroup(this);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineDarkBlue, 1);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineDarkGreen, 2);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineLightBlue, 3);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineLightGreen, 4);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineOrange, 5);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineRed, 6);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineViolet, 7);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineWhite, 8);
    radio_btn_group_Line_color->addButton(ui->radioButtonLineYellow, 9);

    radio_btn_group_method = new QButtonGroup(this);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemFloat, 1);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemInt, 2);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemStair, 3);
    radio_btn_group_method->addButton(ui->radioButtonDiffAnalys, 4);
    radio_btn_group_method->addButton(ui->radioButtonLibFunc, 5);

    connect(ui->pushButtonLine, &QPushButton::clicked, this, &MainWindow::draw_line);
    connect(ui->pushButtonSpector, &QPushButton::clicked, this, &MainWindow::draw_spector);

}


void display_error_message(const char text[LEN_TEXT_ERROR_MESSAGE])
{
    QMessageBox message;
    message.setWindowTitle("Ошибка!");
    message.setText(text);
    message.exec();
}

void MainWindow::set_color_line()
{
    connect(this->radio_btn_group_Line_color, &QButtonGroup::idClicked, this, [=](int id) {
        if (id == 1)
            drawWidget->colorLine = "background-color: darkBlue;";
        else if (id == 2)
            drawWidget->colorLine = "background-color: darkGreen;";
        else if (id == 3)
            drawWidget->colorLine = "background-color: blue;";
        else if (id == 4)
            drawWidget->colorLine = "background-color: lightGreen;";
        else if (id == 5)
            drawWidget->colorLine = "background-color: darkOrange;";
        else if (id == 6)
            drawWidget->colorLine = "background-color: red;";
        else if (id == 7)
            drawWidget->colorLine = "background-color: darkMagenta;";
        else if (id == 8)
            drawWidget->colorLine = "background-color: white;";
        else if (id == 9)
            drawWidget->colorLine = "background-color: yellow;";
    });
}

void MainWindow::set_color_BG()
{
    connect(this->radio_btn_group_BG_color, &QButtonGroup::idClicked, this, [=](int id) {
        if (id == 1)
            drawWidget->colorBG = "background-color: darkBlue;";
        else if (id == 2)
            drawWidget->colorBG = "background-color: darkGreen;";
        else if (id == 3)
            drawWidget->colorBG = "background-color: blue;";
        else if (id == 4)
            drawWidget->colorBG = "background-color: lightGreen;";
        else if (id == 5)
            drawWidget->colorBG = "background-color: darkOrange;";
        else if (id == 6)
            drawWidget->colorBG = "background-color: red;";
        else if (id == 7)
            drawWidget->colorBG = "background-color: darkMagenta;";
        else if (id == 8)
            drawWidget->colorBG = "background-color: white;";
        else if (id == 9)
            drawWidget->colorBG = "background-color: yellow;";
    });
}

void MainWindow::draw_line()
{
    QString data_xs = ui->lineEditXS->text();
    QString data_ys = ui->lineEditYS->text();
    QString data_xf = ui->lineEditXF->text();
    QString data_yf = ui->lineEditYF->text();
    double xs, ys, xf, yf;
    int error = 0;
    bool result;
    xs = data_xs.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе начала отрезка по X!");
    }
    ys = data_ys.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе начала отрезка по Y!");
    }
    xf = data_xf.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе конца отрезка по X!");
    }
    yf = data_yf.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе конца отрезка по Y!");
    }
    if (error == 0)
    {
        set_color_line();
        set_color_BG();
        ui->widget->setStyleSheet(drawWidget->colorBG.c_str());
        drawWidget->line.xs = xs;
        drawWidget->line.ys = ys;
        drawWidget->line.xf = xf;
        drawWidget->line.yf = yf;
    }
    drawWidget->update();
}

void MainWindow::draw_spector()
{
    QString data_angle = ui->lineEditAngle->text();
    QString data_lenLine = ui->lineEditSizeofLine->text();
    double angle, lenLine;
    int error = 0;
    char color_result[100];
    bool result;
    angle = data_angle.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе угла поворота!");
    }
    lenLine = data_lenLine.toDouble(&result);
    if (!result)
    {
        error = 1;
        display_error_message("Ошибка при вводе длины отрезка!");
    }
    if (error == 0)
    {
        drawWidget->angle = angle;
        drawWidget->lenLine = lenLine;
    }
    drawWidget->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}
