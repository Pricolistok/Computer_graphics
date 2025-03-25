#include "maindrawer.h"
#include <QColor>

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}


void cnt_diff(double &dX, double &dY, double &L, double xStart, double yStart, double xEnd, double yEnd)
{
    double dx = xEnd - xStart;
    double dy = yEnd - yStart;
    L = std::max(std::abs(dx), std::abs(dy));
    dX = dx / L;
    dY = dy / L;
}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor qcolorLine = QColor(colorLine.c_str());
    painter.setPen(qcolorLine);

    double offset_to_center_x = WIDTH_CANVAS / 2;
    double offset_to_center_y = HEIGHT_CANVAS / 2;

    double xStart = line.xs;
    double yStart = line.ys;
    double xEnd = line.xf;
    double yEnd = line.yf;

    double dX, dY, x = xStart, y = yStart, L;

    switch (method)
    {
        case DIFF:
            cnt_diff(dX, dY, L, xStart, yStart, xEnd, yEnd);
            for (int i = 0; i <= L; i++) {
                painter.drawPoint(offset_to_center_x + std::round(x), offset_to_center_y - std::round(y));
                x += dX;
                y += dY;
            }
            break;
        default:
            break;

    }

    Q_UNUSED(event);
}

