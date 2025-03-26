#ifndef MAINDRAWER_H

#define MAINDRAWER_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QMainWindow>
#include <QPainterPath>
using namespace std;

#define WIDTH_CANVAS 1000
#define HEIGHT_CANVAS 700
#define SIZE_OF_SPECTOR 1000
#define CNT_LINES 100000

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
} color_t;

typedef struct line
{
    double xs;
    double ys;
    double xf;
    double yf;
    method_t method;
    std::string colorLine;
} line_t;

class MyDrawWidget : public QWidget
{
Q_OBJECT

public:
    bool flag_time_analysis = false;
    vector <line_t> lines;
    vector <double> time_analysis;
    vector <int> cntSteps;
    bool flag_free = false;
    method_t method;
    std::string colorLine;
    std::string colorBG;
    explicit MyDrawWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif
