#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <iostream>
#include <string>
#include <exception>
#include <math.h>
#include <format>
#include <cfloat>

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
    connect(ui->pushBtnRMDot, SIGNAL(clicked()), this, SLOT(rm_dot()));
}

int check_num(QString num)
{
    bool result;
    num.toDouble(&result);
    return result;

}

void send_error_message(string text)
{
    QMessageBox message;
    message.setWindowTitle("Ошибка!");
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

    drawWidget->x_data.clear();
    drawWidget->y_data.clear();
    drawWidget->setShouldDraw(true);
    ui->widget->update();

    int cnt_dots = ui->tableWidget->rowCount();

    for (int i = 0; i < cnt_dots; i++)
    {
        data = ui->tableWidget->item(i, 0)->text();
        if (!check_num(data))
        {
            result_message = snprintf(buffer, 100, "Ошибка! Ошибка в строке %d, с параметром X!", i + 1);
            str_mes = buffer;
            send_error_message(str_mes);
            return;
        }

        data = ui->tableWidget->item(i, 1)->text();
        if (!check_num(data))
        {
            result_message = snprintf(buffer, 100, "Ошибка! Ошибка в строке %d, с параметром Y!", i + 1);
            str_mes = buffer;
            send_error_message(str_mes);
            return;
        }

        drawWidget->x_data.push_back(ui->tableWidget->item(i, 0)->text().toDouble());
        drawWidget->y_data.push_back(ui->tableWidget->item(i, 1)->text().toDouble());
        cout << i << " " << ui->tableWidget->item(i, 0)->text().toStdString() << " " << ui->tableWidget->item(i, 1)->text().toStdString() << endl;
    }

    if (drawWidget->x_data.empty() || drawWidget->y_data.empty()) {
        send_error_message("Ошибка! Данные отсутствуют!");
        return;
    }
}


void MainWindow::add_row()
{
    QString x_position_str = ui->lineEdit_X->text();
    QString y_position_str = ui->lineEdit_Y->text();
    if (!check_num(x_position_str))
    {
        send_error_message("Ошибка! Ошибка при введение X!");
        return;
    }
    if (!check_num(y_position_str))
    {
        send_error_message("Ошибка! Ошибка при введение Y!");
        return;
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(x_position_str));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(y_position_str));
}

void MainWindow::clear_table()
{
    drawWidget->x_data.clear();
    drawWidget->y_data.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels({"X", "Y"});
    ui->tableWidget->setRowCount(0);
}

void MainWindow::rm_dot()
{
    QString input_data = ui->lineEditRMId->text();
    if (!check_num(input_data))
    {
        send_error_message("Ошибка! В номере точки ошибка!");
        return;
    }
    if (input_data.toInt() > ui->tableWidget->rowCount() - 1 || input_data.toInt() <= 0)
    {
        send_error_message("Ошибка! Такого индекса не существует!");
        return;
    }
    ui->tableWidget->removeRow(ui->lineEditRMId->text().toInt() - 1);
}

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: black;");
}

double cnt_bisector(double a, double b, double c)
{
    return sqrt(a * c * (a + c + b) * (a + c - b)) / (a + c);
}

double cnt_size_of_line(double x_data_1, double x_data_2, double y_data_1, double y_data_2)
{
    return sqrt(pow(x_data_1 - x_data_2, 2) + pow(y_data_1 - y_data_2, 2));
}
void message_result(double arr_result[])
{
    QMessageBox message_result;
    QString message;
    message_result.setWindowTitle("Результат");
    message = QString(
                  "Координаты треугольника у которого минимальная биссектриса:\nX1:%1 Y1:%2\nX2:%3 Y2:%4\nX3:%5 Y3:%6\n"
                  "Координаты начала биссектрисы:\nX:%7 Y:%8\nКоординаты конца биссетрисы:\nX:%9 Y:%10\nДлина биссектрисы:%11\n")
                  .arg(arr_result[0]).arg(arr_result[1]).arg(arr_result[2]).arg(arr_result[3]).arg(arr_result[4]).arg(arr_result[5])
                  .arg(arr_result[8]).arg(arr_result[9]).arg(arr_result[6]).arg(arr_result[7]).arg(arr_result[10]);
    message_result.setText(message);
    message_result.exec();
}

bool check_in_one_line(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return abs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) <= 1e-6;
}

double cnt_x_bis(double a, double b, double x1, double x2)
{
    return (a * x1 + b * x2) / (a + b);
}

double cnt_y_bis(double a, double b, double y1, double y2)
{
    return (a * y1 + b * y2) / (a + b);
}

void findCanonicalParams(double x1, double y1, double x2, double y2, double arr_res[])
{
    arr_res[0] = y2 - y1;
    arr_res[1] = x1 - x2;
    arr_res[2] = y1 * x2 - x1 * y2;

}


void line_intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double* intersection_x, double* intersection_y)
{
    double a[3];
    double b[3];
    findCanonicalParams(x3, y3, x4, y4, b);
    findCanonicalParams(x1, y1, x2, y2, a);

    double x = (a[1] * b[2] - b[1] * a[2]) / (b[1] * a[0] - a[1] * b[0]);
    double y = (b[0] * a[2] - a[0] * b[2]) / (a[0] * b[1] - b[0] * a[1]);
    *intersection_x = x;
    *intersection_y = y;
}

bool are_points_distinct(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x1 != x2 || y1 != y2) && (x1 != x3 || y1 != y3) && (x2 != x3 || y2 != y3);
}

void set_data(double arr_result[], double x_1, double y_1, double x_2, double y_2, double x_3, double y_3, double b, double c)
{
    double x_tmp, x_s;
    double y_tmp, y_s;
    arr_result[0] = x_1;
    arr_result[1] = y_1;
    arr_result[2] = x_2;
    arr_result[3] = y_2;
    arr_result[4] = x_3;
    arr_result[5] = y_3;
    x_tmp = cnt_x_bis(b, c, x_2, x_3);
    y_tmp = cnt_y_bis(b, c, y_2, y_3);
    qDebug() << "   x_tmp: " << x_tmp << "  y_tmp: " << y_tmp;
    line_intersection(x_1, y_1, x_tmp, y_tmp, x_2, y_2, x_3, y_3, &x_s, &y_s);
    qDebug() << "   x_s: " << x_s << "  y_s: " << y_s;

    arr_result[6] = x_s;
    arr_result[7] = y_s;
    arr_result[8] = x_1;
    arr_result[9] = y_1;
}


void MyDrawWidget::analisys_dots(double arr_result[11])
{
    double a, b, c, tmp;
    int len_data = int(this->x_data.size());
    double min = DBL_MAX;

    qDebug() << x_data;
    qDebug() << len_data;
    for (int i = 0; i < len_data; i++)
    {
        for (int j = i + 1; j < len_data; j++)
        {
            for (int z = j + 1; z < len_data; z++)
            {
                if (!are_points_distinct(x_data[i], y_data[i], x_data[j], y_data[j], x_data[z], y_data[z]))
                {
                    send_error_message("Ошибка! Есть равные одинаковые точки!");
                    return;
                }

                if (check_in_one_line(x_data[i], y_data[i], x_data[j], y_data[j], x_data[z], y_data[z]))
                {
                    send_error_message("Ошибка! Есть три точки лежат на одной прямой!");
                    continue;
                }

                a = sqrt(pow(x_data[j] - x_data[i], 2) + pow(y_data[j] - y_data[i], 2));
                b = sqrt(pow(x_data[j] - x_data[z], 2) + pow(y_data[j] - y_data[z], 2));
                c = sqrt(pow(x_data[z] - x_data[i], 2) + pow(y_data[z] - y_data[i], 2));

                tmp = cnt_bisector(a, b, c);
                if (tmp < min)
                {
                    qDebug() << "1IF" << tmp << "ВЕРШИНА X: " << x_data[i] << "Y: " << y_data[i];
                    min = tmp;
                    set_data(arr_result, x_data[i], y_data[i], x_data[j], y_data[j], x_data[z], y_data[z], c, a);
                }

                tmp = cnt_bisector(b, c, a);
                if (tmp < min)
                {
                    qDebug() << "2IF" << tmp << "ВЕРШИНА X: " << x_data[j] << "Y: " << y_data[j];
                    min = tmp;
                    set_data(arr_result, x_data[j], y_data[j], x_data[i], y_data[i], x_data[z], y_data[z], b, a);
                }

                tmp = cnt_bisector(c, a, b);
                if (tmp < min)
                {
                    qDebug() << "1IF" << tmp << "ВЕРШИНА X: " << x_data[z] << "Y: " << y_data[z];
                    min = tmp;
                    set_data(arr_result, x_data[z], y_data[z], x_data[i], y_data[i], x_data[j], y_data[j], b, c);
                }
            }
        }
    }
    arr_result[10] = tmp;
}


double cnt_scale(double arr_result[], int len, int screen_width, int screen_height)
{
    int padding = 45;
    double width;
    double height;
    double min_x, max_x;
    double min_y, max_y;

    min_x = min({arr_result[0], arr_result[2], arr_result[4], arr_result[6]});
    max_x = max({arr_result[0], arr_result[2], arr_result[4], arr_result[6]});
    min_y = min({arr_result[1], arr_result[3], arr_result[5], arr_result[7]});
    max_y = max({arr_result[1], arr_result[3], arr_result[5], arr_result[7]});

    width = max_x - min_x;
    height = max_y - min_y;

    if (width == 0 || height == 0)
        return 1;

    double scale_x = (screen_width - 2 * padding) / (double)width;
    double scale_y = (screen_height - 2 * padding) / (double)height;

    return min(scale_x, scale_y);
}


void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.end();
    double arr[11], scale;
    int len_data = int(this->x_data.size());
    int min_x, max_x;
    int min_y, max_y;

    if (len_data < 3)
    {
        if (this->flag_cnt != 0)
            send_error_message("Ошибка! Отсутствуют данные!");
        this->flag_cnt += 1;
        return;
    }

    analisys_dots(arr);

    min_x = min({arr[0], arr[2], arr[4], arr[6]});
    max_x = max({arr[0], arr[2], arr[4], arr[6]});
    min_y = min({arr[1], arr[3], arr[5], arr[7]});
    max_y = max({arr[1], arr[3], arr[5], arr[7]});

    scale = cnt_scale(arr, 10, 1000, 600);

    int figure_width = (max_x - min_x) * scale;
    int figure_height = (max_y - min_y) * scale;

    int offset_x = (1000 - figure_width) / 2 - min_x * scale + 30;
    int offset_y = (600 - figure_height) / 2 + max_y * scale + 30;

    painter.begin(this);
    painter.setPen({Qt::green, 2});
    painter.drawLine(arr[0] * scale + offset_x, arr[1] * scale * -1 + offset_y, arr[2] * scale + offset_x, arr[3] * scale * -1 + offset_y);
    painter.drawLine(arr[0] * scale + offset_x, arr[1] * scale * -1 + offset_y, arr[4] * scale + offset_x, arr[5] * scale * -1 + offset_y);
    painter.drawLine(arr[2] * scale + offset_x, arr[3] * scale * -1 + offset_y, arr[4] * scale + offset_x, arr[5] * scale * -1 + offset_y);

    painter.setPen({Qt::yellow, 2});
    painter.drawLine(arr[6] * scale + offset_x, arr[7] * scale * -1 + offset_y, arr[8] * scale + offset_x, arr[9] * scale * -1 + offset_y);
    if (arr[10] != 0)
        message_result(arr);
    else
        send_error_message("Ошибка! Не найдено ни одного треугольника!");
}




MainWindow::~MainWindow()
{
    delete ui;
}
