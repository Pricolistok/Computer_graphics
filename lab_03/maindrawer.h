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

typedef enum method
{
    DIFF,
    BRENZENHEM_FLOAT,
    BRENZENHEM_INT,
    BRENZENHEM_STAIR,
    VU,
    LIB_FUNC
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
} line_t;

class MyDrawWidget : public QWidget
{
Q_OBJECT

public:
    method_t method;
    std::string colorLine;
    std::string colorBG;
    line_t line;
    line_t spector[SIZE_OF_SPECTOR];
    double angle;
    double lenLine;
    explicit MyDrawWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif
