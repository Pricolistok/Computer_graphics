#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <unistd.h>

using namespace std;

void cnt_rotate_result(double &x, double &y, double angle)
{
    double temp_x, temp_y;
    double new_angle = angle * M_PI / 180;
    temp_x = x;
    temp_y = y;
    x = (temp_x * cos(new_angle)) - (temp_y * sin(new_angle));
    y = (temp_x * sin(new_angle)) + (temp_y * cos(new_angle));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("CG lab_03");
    ui->widget->setStyleSheet("background-color:white;");
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
    connect(ui->pushButtonClearDisp, &QPushButton::clicked, this, &MainWindow::set_free);
    connect(ui->pushButtonTimeData, &QPushButton::clicked, this, &MainWindow::set_data_time);

}

void MainWindow::set_data_time()
{
    drawWidget->lines.clear();
    drawWidget->time_analysis.clear();
    ui->widget->setStyleSheet("background-color: white;");

    line_t line;
    line.xs = 0;
    line.ys = 0;
    line.xf = 1000;
    line.yf = 0;
    line.method = DIFF;
    line.colorLine = "white";
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_FLOAT;
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_INT;
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_STAIR;
    drawWidget->lines.push_back(line);
    line.method = WU;
    drawWidget->lines.push_back(line);

    line.xs = 0;
    line.ys = 0;
    line.xf = 707;
    line.yf = 707;
    line.method = DIFF;
    line.colorLine = "white";
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_FLOAT;
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_INT;
    drawWidget->lines.push_back(line);
    line.method = BRENZENHEM_STAIR;
    drawWidget->lines.push_back(line);
    line.method = WU;
    drawWidget->lines.push_back(line);

    drawWidget->draw = false;
    drawWidget->repaint();

    QTimer::singleShot(0, this, [this]() {
        FILE *file = fopen("data_time.txt", "w");
        if (file)
        {
            for (size_t i = 0; i < drawWidget->lines.size() - 5; i++) {
                fprintf(file, "%lf %lf\n", drawWidget->time_analysis[5 + i], drawWidget->time_analysis[5 + i]);
            }
            fflush(file);
            fclose(file);
        }
        else
            qDebug() << "Error opening file";

        drawWidget->cntSteps.clear();
        drawWidget->lines.clear();

        line_t line_rotate;
        int angle_rotate = 0;
        double xf = 1000, yf = 0;
        while (angle_rotate <= 90)
        {
            line_rotate.xs = 0;
            line_rotate.ys = 0;
            line_rotate.xf = xf;
            line_rotate.yf = yf;
            line_rotate.colorLine = "white";
            line_rotate.method = DIFF;
            drawWidget->lines.push_back(line_rotate);
            line_rotate.method = BRENZENHEM_FLOAT;
            drawWidget->lines.push_back(line_rotate);
            line_rotate.method = BRENZENHEM_INT;
            drawWidget->lines.push_back(line_rotate);
            line_rotate.method = BRENZENHEM_STAIR;
            drawWidget->lines.push_back(line_rotate);
            line_rotate.method = WU;
            drawWidget->lines.push_back(line_rotate);
            cnt_rotate_result(xf, yf, 5);
            angle_rotate += 5;
        }
        drawWidget->draw = false;
        drawWidget->repaint();
        QTimer::singleShot(0, this, [this]()
        {
            FILE *file_stair = fopen("data_stair.txt", "w");
            if (file_stair) {
                for (size_t i = 0; i < 5; i++) {
                    for (size_t j = i; j < drawWidget->cntSteps.size(); j += 5)
                        fprintf(file_stair, "%d ", drawWidget->cntSteps[j]);
                    fprintf(file_stair, "\n");
                }
                fflush(file_stair);
                fclose(file_stair);
            } else
                qDebug() << "Error opening file";
            QTimer::singleShot(0, this, [this]()
            {
                drawWidget->cntSteps.clear();
                drawWidget->lines.clear();
                drawWidget->update();
                system("python main.py");
            });
        });
    });
}


void MainWindow::set_free()
{
    drawWidget->flag_free = true;
    drawWidget->lines.clear();
    drawWidget->time_analysis.clear();
    drawWidget->update();
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
    if (fabs(xs - xf) <= 1e-6 && fabs(ys - yf) <= 1e-6)
    {
        error = 1;
        display_error_message("Отрезок вырожден!");
    }

    if (error == 0)
    {
        line_t line;
        line.xs = xs;
        line.ys = ys;
        line.xf = xf;
        line.yf = yf;
        line.method = drawWidget->method;
        line.colorLine = drawWidget->colorLine;
        drawWidget->lines.push_back(line);
        ui->widget->setStyleSheet(drawWidget->colorBG.c_str());
        drawWidget->flag_free = false;
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
    if (lenLine <= 1e-6)
    {
        error = 1;
        display_error_message("Ошибка при вводе длины! Длина меньше или равна 0!");
    }
    if (fabs(angle) <= 1e-6)
    {
        error = 1;
        display_error_message("Ошибка при вводе угла! Угол равен 0!");
    }
    if (error == 0)
    {
        if (angle < 0)
            angle *= -1;
        double angle_rotate = 0;
        line_t line;
        ui->widget->setStyleSheet(drawWidget->colorBG.c_str());
        drawWidget->flag_free = false;
        double xf = lenLine, yf = 0;
        while (angle_rotate <= 360)
        {
            line.xs = 0;
            line.ys = 0;
            line.xf = xf;
            line.yf = yf;
            line.method = drawWidget->method;
            line.colorLine = drawWidget->colorLine;
            drawWidget->lines.push_back(line);
            cnt_rotate_result(xf, yf, angle);
            angle_rotate += angle;
        }
        drawWidget->update();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
