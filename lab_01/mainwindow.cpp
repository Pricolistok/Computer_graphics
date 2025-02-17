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

    drawWidget->x_data.clear();
    drawWidget->y_data.clear();
    drawWidget->setShouldDraw(true);
    ui->widget->update();

    int cnt_dots = ui->tableWidget->rowCount();

    if (cnt_dots == 0) {
        send_error_message("No data to draw.");
        return;
    }

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

    if (drawWidget->x_data.empty() || drawWidget->y_data.empty()) {
        send_error_message("Error: Data is empty after reset.");
        return;
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
    drawWidget->x_data.clear();
    drawWidget->y_data.clear();
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

double cnt_bisector(double a, double b, double c)
{
    return sqrt(a * c * (a + c + b) * (a + c - b)) / (a + c);
}

double cnt_size_of_line(int x_data_1, int x_data_2, int y_data_1, int y_data_2)
{
    return sqrt(pow(x_data_1 - x_data_2, 2) + pow(y_data_1 - y_data_2, 2));
}
void message_result(int arr_result[], double tmp)
{
    QMessageBox message_result;
    QString message;
    message_result.setWindowTitle("Result");
    message = QString("X1:%1\nY1:%2\nX2:%3\nY2:%4\nX3:%5\nY3:%6\nMin:%7").arg(arr_result[0]).arg(arr_result[1]).arg(arr_result[2]).arg(arr_result[3]).arg(arr_result[4]).arg(arr_result[5]).arg(QString::number(tmp, 'f', 2));
    message_result.setText(message);
    message_result.exec();
}

bool check_in_one_line(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) == 0;
}

int cnt_x_bis(double a, double b, int x1, int x2)
{
    return (a * x2 + b * x1) / (a + b);
}

int cnt_y_bis(double a, double b, int y1, int y2)
{
    return (a * y1 + b * y2) / (a + b);
}

void MyDrawWidget::analisys_dots(int arr_result[10])
{
    double a, b, c, tmp;
    int len_data = int(this->x_data.size());
    double min = DBL_MAX;  // Используем максимально возможное значение для поиска минимальной биссектрисы

    // Перебираем все возможные треугольники
    for (int i = 0; i < len_data; i++)
    {
        for (int j = i + 1; j < len_data; j++)
        {
            for (int z = j + 1; z < len_data; z++)
            {
                // Проверяем, лежат ли точки на одной прямой
                if (check_in_one_line(x_data[i], y_data[i], x_data[j], y_data[j], x_data[z], y_data[z])) {
                    continue;  // Если точки коллинеарны, пропускаем этот набор
                }

                // Считаем длины сторон треугольника
                a = sqrt(pow(x_data[j] - x_data[i], 2) + pow(y_data[j] - y_data[i], 2));
                b = sqrt(pow(x_data[j] - x_data[z], 2) + pow(y_data[j] - y_data[z], 2));
                c = sqrt(pow(x_data[z] - x_data[i], 2) + pow(y_data[z] - y_data[i], 2));

                // Считаем биссектрисы для всех сторон
                tmp = cnt_bisector(a, b, c);
                cout << "Bisector 1: " << tmp << endl;
                if (tmp < min) {
                    min = tmp;
                    arr_result[0] = x_data[i];
                    arr_result[1] = y_data[i];
                    arr_result[2] = x_data[j];
                    arr_result[3] = y_data[j];
                    arr_result[4] = x_data[z];
                    arr_result[5] = y_data[z];
                    arr_result[6] = cnt_x_bis(c, b, x_data[i], x_data[j]);
                    arr_result[7] = cnt_y_bis(c, b, y_data[i], y_data[j]);
                    arr_result[8] = x_data[i];
                    arr_result[9] = y_data[i];
                }

                tmp = cnt_bisector(b, c, a);
                cout << "Bisector 2: " << tmp << endl;
                if (tmp < min) {
                    min = tmp;
                    arr_result[0] = x_data[i];
                    arr_result[1] = y_data[i];
                    arr_result[2] = x_data[j];
                    arr_result[3] = y_data[j];
                    arr_result[4] = x_data[z];
                    arr_result[5] = y_data[z];
                    arr_result[6] = cnt_x_bis(a, c, x_data[i], x_data[z]);
                    arr_result[7] = cnt_y_bis(a, c, y_data[i], y_data[z]);
                    arr_result[8] = x_data[j];
                    arr_result[9] = y_data[j];
                }

                tmp = cnt_bisector(c, a, b);
                cout << "Bisector 3: " << tmp << endl;
                if (tmp < min) {
                    min = tmp;
                    arr_result[0] = x_data[i];
                    arr_result[1] = y_data[i];
                    arr_result[2] = x_data[j];
                    arr_result[3] = y_data[j];
                    arr_result[4] = x_data[z];
                    arr_result[5] = y_data[z];
                    arr_result[6] = cnt_x_bis(b, a, x_data[i], x_data[j]);
                    arr_result[7] = cnt_y_bis(b, a, y_data[i], y_data[j]);
                    arr_result[8] = x_data[z];
                    arr_result[9] = y_data[z];
                }
            }
        }
    }
    message_result(arr_result, min);
}


int cnt_scale(int arr_result[], int len, int screen_width, int screen_height)
{
    // Отступы от краёв экрана
    int padding = 30;

    int min_x = abs(arr_result[0]), max_x = arr_result[0];
    int min_y = abs(arr_result[1]), max_y = arr_result[1];
    int width, height;

    // Поиск минимальных и максимальных координат
    for (int i = 0; i < len; i += 2)
    {
        if (abs(arr_result[i]) < min_x)
            min_x = abs(arr_result[i]);
        if (abs(arr_result[i]) > max_x)
            max_x = abs(arr_result[i]);
    }
    for (int i = 1; i < len; i += 2)
    {
        if (abs(arr_result[i]) < min_y)
            min_y = abs(arr_result[i]);
        if (abs(arr_result[i]) > max_y)
            max_y = abs(arr_result[i]);
    }

    width = max_x - min_x;
    height = max_y - min_y;

    if (width == 0 || height == 0)
        return 1;

    double scale_x = (screen_width - 2 * padding) / (double)max_x;
    double scale_y = (screen_height - 2 * padding) / (double)max_y;
    int scale = min(scale_x, scale_y);
    cout << scale << endl;
    return scale;
}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int arr[10], scale;
    int len_data = int(this->x_data.size());
    painter.setPen({Qt::white, 2});

    // Рисуем оси координат
    painter.drawLine(0, 300, 1000, 300);
    painter.drawLine(990, 295, 1000, 300);
    painter.drawLine(990, 305, 1000, 300);
    painter.drawLine(500, 0, 500, 600);
    painter.drawLine(495, 10, 500, 0);
    painter.drawLine(505, 10, 500, 0);

    // Проверка данных
    if (len_data < 3)
    {
        send_error_message("Error with cnt dots");
        return;
    }

    // Рисуем точки (данные)
    painter.setPen({Qt::red, 2});
    for (int i = 0; i < len_data; i++)
    {
        painter.drawEllipse(QPoint(this->x_data[i] + 500, -1 * this->y_data[i] + 300), 1, 1);
    }

    // Применяем масштабирование
    analisys_dots(arr);
    painter.end();
    painter.begin(this);

    painter.setPen({Qt::green, 2});

    scale = cnt_scale(arr, 10, 500, 300);

    painter.drawLine(arr[0] * scale + 500, arr[1] * scale * -1 + 300, arr[2] * scale + 500, arr[3] * scale * -1 + 300);
    painter.drawLine(arr[0] * scale + 500, arr[1] * scale * -1 + 300, arr[4] * scale + 500, arr[5] * scale * -1 + 300);
    painter.drawLine(arr[2] * scale + 500, arr[3] * scale * -1 + 300, arr[4] * scale + 500, arr[5] * scale * -1 + 300);

    cout << scale << endl;

    // Дополнительные линии
    painter.setPen({Qt::yellow, 2});
    cout << arr[6] << " " << arr[7] << " " << arr[8] << " " << arr[9] << endl;
    painter.drawLine(arr[6] * scale + 500, arr[7] * scale * -1 + 300, arr[8] * scale + 500, arr[9] * scale * -1 + 300);
}



MainWindow::~MainWindow()
{
    delete ui;
}
