#include "maindrawer.h"
#include <QColor>
using namespace std;

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void cnt_wu(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY, string colorName)
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

    QColor color(colorName.c_str());
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

void cnt_diff_draw(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY, string color)
{
    QColor color_res = QColor(color.c_str());
    painter.setPen(color_res);
    double dX, dY, L;
    cnt_diff(dX, dY, L, xStart, yStart, xEnd, yEnd);
    double x = xStart, y = yStart;
    for (int i = 0; i <= L; i++) {
        painter.drawPoint(offsetX + std::round(x), offsetY - std::round(y));
        x += dX;
        y += dY;
    }
}

void cnt_bresenham(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY, string color)
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
    QColor color_result = QColor(color.c_str());
    for (int i = 0; i <= dx; i++) {
        painter.setPen(color_result);
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

void cnt_bresenham_real(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY, string color)
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
    QColor color_result = QColor(color.c_str());

    for (int i = 0; i <= dx; i++) {
        painter.setPen(color_result);
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

void bresenhamAntialiased(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd,
                          double offsetX, double offsetY, const std::string &color)
{
    const int I = 255; // Максимальная интенсивность

    // Исходные координаты
    double X0 = xStart;
    double Y0 = yStart;
    double X1 = xEnd;
    double Y1 = yEnd;

    // Проверка вырожденного случая
    if (std::abs(X0 - X1) < 1e-6 && std::abs(Y0 - Y1) < 1e-6) {
        painter.setPen(QColor(color.c_str()));
        painter.drawPoint(offsetX + round(X0), offsetY - round(Y0));
        return;
    }

    // Вычисление приращений
    double dX = X1 - X0;
    double dY = Y1 - Y0;

    // Определение направления движения
    int SX = (dX > 0) ? 1 : -1;
    int SY = (dY > 0) ? 1 : -1;

    dX = std::abs(dX);
    dY = std::abs(dY);

    // Тангенс угла наклона
    double m = (dX == 0) ? 1.0 : dY / dX;

    // Проверка крутизны
    bool steep = m > 1.0;
    if (steep) {
        std::swap(dX, dY);
        m = 1.0 / m;
        std::swap(SX, SY);
    }

    // Начальное значение ошибки
    double f = 0.5 * I;

    // Коэффициенты
    double mI = m * I;
    double W = I - mI;

    QColor lineColor(color.c_str());
    double X = X0;
    double Y = Y0;

    for (int i = 0; i <= dX; i++) {
        double drawX = steep ? Y : X;
        double drawY = steep ? X : Y;

        // Вычисление интенсивности
        double Y_frac = drawY - std::floor(drawY);
        int intensity1 = std::clamp(static_cast<int>((1.0 - Y_frac) * I), 0, 255);
        int intensity2 = std::clamp(static_cast<int>(Y_frac * I), 0, 255);

        // Рисуем пиксели с разной интенсивностью
        lineColor.setAlpha(intensity1);
        painter.setPen(lineColor);
        painter.drawPoint(offsetX + round(drawX), offsetY - std::floor(drawY));

        lineColor.setAlpha(intensity2);
        painter.setPen(lineColor);
        painter.drawPoint(offsetX + round(drawX), offsetY - std::ceil(drawY));

        // Обновление ошибки и координат
        if (f < W) {
            X += SX;
            f += mI;
        } else {
            X += SX;
            Y += SY;
            f -= W;
        }
    }
}




void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    if (flag_free)
        return;
    QPainter painter(this);
    QColor qcolorLine;

    double offset_to_center_x = WIDTH_CANVAS / 2;
    double offset_to_center_y = HEIGHT_CANVAS / 2;

    double xStart, yStart, xEnd, yEnd;
    qDebug() << lines.size();
    for (int i = 0; i < lines.size(); i++)
    {
        xStart = lines[i].xs;
        yStart = lines[i].ys;
        xEnd = lines[i].xf;
        yEnd = lines[i].yf;
        qDebug() << xStart ;
        switch (lines[i].method) {
            case DIFF:
                cnt_diff_draw(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine);
                break;
            case BRENZENHEM_INT:
                cnt_bresenham(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine);
                break;
            case BRENZENHEM_FLOAT:
                cnt_bresenham_real(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine);
                break;
            case BRENZENHEM_STAIR:
                bresenhamAntialiased(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x,
                                          offset_to_center_y, lines[i].colorLine);
                break;
            case LIB_FUNC:
                qcolorLine = QColor(lines[i].colorLine.c_str());
                painter.setPen(qcolorLine);
                painter.drawLine(round(xStart + offset_to_center_x), round(-yStart + offset_to_center_y),
                                 round(xEnd + offset_to_center_x),
                                 round(-yEnd + offset_to_center_y));
                break;
            case WU:
                cnt_wu(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine);
                break;
            default:
                break;
        }
    }

    Q_UNUSED(event);
}


