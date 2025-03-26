#include "maindrawer.h"
#include <QColor>

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void MyDrawWidget::cnt_rotate_result(double &x, double &y)
{
    double temp_x, temp_y;
    double new_angle = -this->angle_spector * M_PI / 180;
    temp_x = x;
    temp_y = y;
    x = (temp_x * cos(new_angle)) - (temp_y * sin(new_angle));
    y = (temp_x * sin(new_angle)) + (temp_y * cos(new_angle));
}

void cnt_wu(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY)
{
    auto ipart = [](double x) { return std::floor(x); };
    auto round = [](double x) { return std::floor(x + 0.5); };
    auto fpart = [](double x) { return x - std::floor(x); };
    auto rfpart = [&](double x) { return 1.0 - fpart(x); };

    bool steep = std::abs(yEnd - yStart) > std::abs(xEnd - xStart);
    if (steep) {
        std::swap(xStart, yStart);
        std::swap(xEnd, yEnd);
    }

    if (xStart > xEnd) {
        std::swap(xStart, xEnd);
        std::swap(yStart, yEnd);
    }

    double dx = xEnd - xStart;
    double dy = yEnd - yStart;
    double gradient = (dx == 0.0) ? 1.0 : dy / dx;

    double xEndRounded = round(xStart);
    double yEndInterpolated = yStart + gradient * (xEndRounded - xStart);
    double xGap = rfpart(xStart + 0.5);
    int xPixel1 = static_cast<int>(xEndRounded);
    int yPixel1 = static_cast<int>(ipart(yEndInterpolated));

    QColor color(0, 0, 0);
    color.setAlphaF(rfpart(yEndInterpolated) * xGap);
    painter.setPen(color);
    if (steep)
        painter.drawPoint(offsetX + yPixel1, offsetY - xPixel1);
    else
        painter.drawPoint(offsetX + xPixel1, offsetY - yPixel1);

    color.setAlphaF(fpart(yEndInterpolated) * xGap);
    painter.setPen(color);
    if (steep)
        painter.drawPoint(offsetX + yPixel1 + 1, offsetY - xPixel1);
    else
        painter.drawPoint(offsetX + xPixel1, offsetY - yPixel1 - 1);

    double intery = yEndInterpolated + gradient;

    xEndRounded = round(xEnd);
    yEndInterpolated = yEnd + gradient * (xEndRounded - xEnd);
    xGap = fpart(xEnd + 0.5);
    int xPixel2 = static_cast<int>(xEndRounded);
    int yPixel2 = static_cast<int>(ipart(yEndInterpolated));

    color.setAlphaF(rfpart(yEndInterpolated) * xGap);
    painter.setPen(color);
    if (steep)
        painter.drawPoint(offsetX + yPixel2, offsetY - xPixel2);
    else
        painter.drawPoint(offsetX + xPixel2, offsetY - yPixel2);

    color.setAlphaF(fpart(yEndInterpolated) * xGap);
    painter.setPen(color);
    if (steep)
        painter.drawPoint(offsetX + yPixel2 + 1, offsetY - xPixel2);
    else
        painter.drawPoint(offsetX + xPixel2, offsetY - yPixel2 - 1);

    for (int x = xPixel1 + 1; x < xPixel2; x++) {
        int y = static_cast<int>(ipart(intery));

        color.setAlphaF(rfpart(intery));
        painter.setPen(color);
        if (steep)
            painter.drawPoint(offsetX + y, offsetY - x);
        else
            painter.drawPoint(offsetX + x, offsetY - y);

        color.setAlphaF(fpart(intery));
        painter.setPen(color);
        if (steep)
            painter.drawPoint(offsetX + y + 1, offsetY - x);
        else
            painter.drawPoint(offsetX + x, offsetY - y - 1);

        intery += gradient;
    }
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
    if (method == FREE)
        return;
    QPainter painter(this);
    QColor qcolorLine = QColor(colorLine.c_str());
    painter.setPen(qcolorLine);

    double offset_to_center_x = WIDTH_CANVAS / 2;
    double offset_to_center_y = HEIGHT_CANVAS / 2;

    double xStart, yStart, xEnd, yEnd;

    if (!spector_flag)
    {
        for (int i = 0; i < dataLine.cnt_lines; i++)
        {
            xStart = dataLine.lines[i].xs;
            yStart = dataLine.lines[i].ys;
            xEnd = dataLine.lines[i].xf;
            yEnd = dataLine.lines[i].yf;
            switch (dataLine.lines[i].method) {
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
                    cnt_bresenham_antialiased(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x,
                                              offset_to_center_y);
                    break;
                case LIB_FUNC:
                    painter.drawLine(round(xStart + offset_to_center_x), round(-yStart + offset_to_center_y),
                                     round(xEnd + offset_to_center_x),
                                     round(-yEnd + offset_to_center_y));
                    break;
                case WU:
                    cnt_wu(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        xStart = 0;
        yStart = 0;
        xEnd = lenLine;
        yEnd = 0;
        double angle = 0;
        while (angle <= 360)
        {
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
                    painter.drawLine(xStart + offset_to_center_x, -yStart + offset_to_center_y, xEnd + offset_to_center_x,-yEnd + offset_to_center_y);
                    break;
                case WU:
                    cnt_wu(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y);
                    break;
                default:
                    break;
            }
            cnt_rotate_result(xEnd, yEnd);
            angle += angle_spector;
        }
        spector_flag = false;
    }

    Q_UNUSED(event);
}


