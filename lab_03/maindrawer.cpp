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

void cnt_diff_draw(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY)
{
    double dX, dY, L;
    cnt_diff(dX, dY, L, xStart, yStart, xEnd, yEnd);
    double x = xStart, y = yStart;
    for (int i = 0; i <= L; i++) {
        painter.drawPoint(offsetX + std::round(x), offsetY - std::round(y));
        x += dX;
        y += dY;
    }
}

void cnt_bresenham(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY)
{
    int x0 = std::round(xStart);
    int y0 = std::round(yStart);
    int x1 = std::round(xEnd);
    int y1 = std::round(yEnd);

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    bool swapXY = dy > dx;
    if (swapXY) {
        std::swap(dx, dy);
    }

    int error = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
        painter.drawPoint(offsetX + x0, offsetY - y0);

        while (error >= 0) {
            if (swapXY) {
                x0 += sx;
            } else {
                y0 += sy;
            }
            error -= 2 * dx;
        }

        if (swapXY) {
            y0 += sy;
        } else {
            x0 += sx;
        }
        error += 2 * dy;
    }
}

void cnt_bresenham_real(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY)
{
    double dx = xEnd - xStart;
    double dy = yEnd - yStart;
    int sx = (dx >= 0) ? 1 : -1;
    int sy = (dy >= 0) ? 1 : -1;

    dx = std::abs(dx);
    dy = std::abs(dy);

    bool swapXY = dy > dx;
    if (swapXY) {
        std::swap(dx, dy);
    }

    double m = dy / dx;
    double f = m - 0.5;

    int x = std::round(xStart);
    int y = std::round(yStart);

    for (int i = 0; i <= dx; i++) {
        painter.drawPoint(offsetX + x, offsetY - y);

        if (f >= 0) {
            if (swapXY) x += sx;
            else y += sy;
            f -= 1;
        }

        if (swapXY) y += sy;
        else x += sx;

        f += m;
    }
}

void cnt_bresenham_antialiased(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY)
{
    int x = std::round(xStart);
    int y = std::round(yStart);
    int x1 = std::round(xEnd);
    int y1 = std::round(yEnd);

    int dx = std::abs(x1 - x);
    int dy = std::abs(y1 - y);
    int sx = (x < x1) ? 1 : -1;
    int sy = (y < y1) ? 1 : -1;
    bool swapXY = dy > dx;
    if (swapXY) {
        std::swap(dx, dy);
    }

    double m = (double)dy / dx;
    double f = 0.5;
    double I = 255.0;
    double W = I - m * I;

    for (int i = 0; i <= dx; i++) {
        int intensity = static_cast<int>(I * (1 - f));
        QColor color(0, 0, 0, intensity);
        painter.setPen(color);
        painter.drawPoint(offsetX + x, offsetY - y);

        if (f < W) {
            if (!swapXY) x += sx;
            else y += sy;
            f += m * I;
        } else {
            x += sx;
            y += sy;
            f -= W;
        }
    }
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

    switch (method)
    {
        case DIFF:
            cnt_diff_draw(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
            break;
        case BRENZENHEM_INT:
            cnt_bresenham(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
            break;
        case BRENZENHEM_FLOAT:
            cnt_bresenham_real(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
            break;
        case BRENZENHEM_STAIR:
            cnt_bresenham_antialiased(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
            break;
        case LIB_FUNC:
            painter.drawLine(xStart + offset_to_center_x, -yStart + offset_to_center_y, xEnd + offset_to_center_x, -yEnd + offset_to_center_y);
        default:
            break;
    }

    Q_UNUSED(event);
}


