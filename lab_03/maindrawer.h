#ifndef MAINDRAWER_H

#define MAINDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QMainWindow>
#include <QPainterPath>

#define WIDTH_CANVAS 1000
#define HEIGHT_CANVAS 700
#define SIZE_OF_SPECTOR 1000
#define CNT_LINES 1000

typedef enum method
{
    DIFF,
    BRENZENHEM_FLOAT,
    BRENZENHEM_INT,
    BRENZENHEM_STAIR,
    WU,
    LIB_FUNC,
    FREE,
    DRAW
} method_t;

typedef enum color
{
    darkBlue,
    darkGreen,
    blue,
    lightGreen,
    darkOrange,
    red,
    darkMagenta,
    white,
    yellow
} color;

typedef struct line
{
    double xs;
    double ys;
    double xf;
    double yf;
    method_t method;
} line_t;

typedef struct data_line
{
    line_t lines[CNT_LINES];
    int cnt_lines = 0;
} data_line_t;

class MyDrawWidget : public QWidget
{
Q_OBJECT

public:
    data_line_t dataLine;
    bool spector_flag = false;
    double angle_spector;
    double size_of_line;
    method_t method;
    std::string colorLine;
    std::string colorBG;
    line_t line;
    double lenLine;
    void cnt_rotate_result(double &x, double &y);
    explicit MyDrawWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif
