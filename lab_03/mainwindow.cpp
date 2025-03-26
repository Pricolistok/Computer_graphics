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
    radio_btn_group_BG_color->addButton(ui->radioButtonBgBlack, 10);

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
    radio_btn_group_Line_color->addButton(ui->radioButtonLineBlack, 10);

    radio_btn_group_method = new QButtonGroup(this);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemFloat, 1);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemInt, 2);
    radio_btn_group_method->addButton(ui->radioButtonBrenzenhemStair, 3);
    radio_btn_group_method->addButton(ui->radioButtonDiffAnalys, 4);
    radio_btn_group_method->addButton(ui->radioButtonLibFunc, 5);
    radio_btn_group_method->addButton(ui->radioButtonVu, 6);

    drawWidget->colorBG = "background-color: white;";
    drawWidget->colorLine = "black";
    drawWidget->method = LIB_FUNC;
    ui->radioButtonBgWhite->setChecked(true);
    ui->radioButtonLineBlack->setChecked(true);
    ui->radioButtonLibFunc->setChecked(true);

    connect(radio_btn_group_Line_color, &QButtonGroup::idClicked, this, &MainWindow::set_color_line);
    connect(radio_btn_group_BG_color, &QButtonGroup::idClicked, this, &MainWindow::set_color_BG);
    connect(radio_btn_group_method, &QButtonGroup::idClicked, this, &MainWindow::set_method);

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

void MainWindow::set_method(int id)
{
    switch (id)
    {
        case 1:
            drawWidget->method = BRENZENHEM_FLOAT;
            break;
        case 2:
            drawWidget->method = BRENZENHEM_INT;
            break;
        case 3:
            drawWidget->method = BRENZENHEM_STAIR;
            break;
        case 4:
            drawWidget->method = DIFF;
            break;
        case 5:
            drawWidget->method = LIB_FUNC;
            break;
        case 6:
            drawWidget->method = WU;
            break;
        default:
            break;
    }
}


void MainWindow::set_color_line(int id)
{
    switch (id)
    {
        case 1:
            drawWidget->colorLine = "darkBlue";
            break;
        case 2:
            drawWidget->colorLine = "darkGreen";
            break;
        case 3:
            drawWidget->colorLine = "blue";
            break;
        case 4:
            drawWidget->colorLine = "lightGreen";
            break;
        case 5:
            drawWidget->colorLine = "orange";
            break;
        case 6:
            drawWidget->colorLine = "red";
            break;
        case 7:
            drawWidget->colorLine = "purple";
            break;
        case 8:
            drawWidget->colorLine = "white";
            break;
        case 9:
            drawWidget->colorLine = "yellow";
            break;
        case 10:
            drawWidget->colorLine = "black";
            break;
        default:
            break;
    }
}

void MainWindow::set_color_BG(int id)
{
    switch (id)
    {
        case 1:
            drawWidget->colorBG = "background-color: darkBlue;";
            break;
        case 2:
            drawWidget->colorBG = "background-color: darkGreen;";
            break;
        case 3:
            drawWidget->colorBG = "background-color: blue;";
            break;
        case 4:
            drawWidget->colorBG = "background-color: lightGreen;";
            break;
        case 5:
            drawWidget->colorBG = "background-color: Orange;";
            break;
        case 6:
            drawWidget->colorBG = "background-color: red;";
            break;
        case 7:
            drawWidget->colorBG = "background-color: purple;";
            break;
        case 8:
            drawWidget->colorBG = "background-color: white;";
            break;
        case 9:
            drawWidget->colorBG = "background-color: yellow;";
            break;
        case 10:
            drawWidget->colorBG = "background-color: black;";
            break;
        default:
            break;
    }
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
        ui->widget->setStyleSheet(drawWidget->colorBG.c_str());
        drawWidget->dataLine.lines[drawWidget->dataLine.cnt_lines].xs = xs;
        drawWidget->dataLine.lines[drawWidget->dataLine.cnt_lines].ys = ys;
        drawWidget->dataLine.lines[drawWidget->dataLine.cnt_lines].xf = xf;
        drawWidget->dataLine.lines[drawWidget->dataLine.cnt_lines].yf = yf;
        drawWidget->dataLine.lines[drawWidget->dataLine.cnt_lines].method = drawWidget->method;
        drawWidget->dataLine.cnt_lines += 1;
        drawWidget->update();
    }
}

void MainWindow::draw_spector()
{
    QString data_angle = ui->lineEditAngle->text();
    QString data_lenLine = ui->lineEditSizeofLine->text();
    double angle, lenLine;
    int error = 0;
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
        ui->widget->setStyleSheet(drawWidget->colorBG.c_str());
        drawWidget->spector_flag = true;
        drawWidget->angle_spector = angle;
        drawWidget->lenLine = lenLine;
        drawWidget->update();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
