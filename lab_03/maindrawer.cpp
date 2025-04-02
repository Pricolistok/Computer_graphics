#include "maindrawer.h"
#include <QColor>
#include <x86intrin.h>
using namespace std;

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void cnt_wu(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd, double offsetX, double offsetY, const std::string &colorName, int &stepCount, bool draw)
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

    int stepCounter = 0;

    // Первый конец
    double xEndRounded = round(xStart);
    double yEndInterpolated = yStart + gradient * (xEndRounded - xStart);
    double xGap = rfpart(xStart + 0.5);
    int xPixel1 = static_cast<int>(xEndRounded);
    int yPixel1 = static_cast<int>(ipart(yEndInterpolated));

    QColor color(colorName.c_str());

    if (draw) {
        color.setAlphaF(rfpart(yEndInterpolated) * xGap);
        painter.setPen(color);
        painter.drawPoint(offsetX + (steep ? yPixel1 : xPixel1), offsetY - (steep ? xPixel1 : yPixel1));

        color.setAlphaF(fpart(yEndInterpolated) * xGap);
        painter.setPen(color);
        painter.drawPoint(offsetX + (steep ? yPixel1 + 1 : xPixel1), offsetY - (steep ? xPixel1 : yPixel1 + 1));
    }

    // Второй конец
    xEndRounded = round(xEnd);
    yEndInterpolated = yEnd + gradient * (xEndRounded - xEnd);
    xGap = fpart(xEnd + 0.5);
    int xPixel2 = static_cast<int>(xEndRounded);
    int yPixel2 = static_cast<int>(ipart(yEndInterpolated));

    if (draw) {
        color.setAlphaF(rfpart(yEndInterpolated) * xGap);
        painter.setPen(color);
        painter.drawPoint(offsetX + (steep ? yPixel2 : xPixel2), offsetY - (steep ? xPixel2 : yPixel2));

        color.setAlphaF(fpart(yEndInterpolated) * xGap);
        painter.setPen(color);
        painter.drawPoint(offsetX + (steep ? yPixel2 + 1 : xPixel2), offsetY - (steep ? xPixel2 : yPixel2 + 1));
    }

    // Основной цикл
    double intery = yPixel1 + gradient;
    int prevX = xPixel1;
    int prevY = yPixel1;

    for (int x = xPixel1 + 1; x < xPixel2; ++x) {
        int y = static_cast<int>(ipart(intery));

        if (y != prevY) {
            ++stepCounter;
            prevY = y;
        }

        if (draw) {
            color.setAlphaF(rfpart(intery));
            painter.setPen(color);
            painter.drawPoint(offsetX + (steep ? y : x), offsetY - (steep ? x : y));

            color.setAlphaF(fpart(intery));
            painter.setPen(color);
            painter.drawPoint(offsetX + (steep ? y + 1 : x), offsetY - (steep ? x : y + 1));
        }

        intery += gradient;
    }
    stepCount = stepCounter;
}

void cnt_diff(double &dX, double &dY, double &L, double xStart, double yStart, double xEnd, double yEnd)
{
    double dx = xEnd - xStart;
    double dy = yEnd - yStart;
    L = std::max(std::abs(dx), std::abs(dy));
    dX = dx / L;
    dY = dy / L;
}

void cnt_diff_draw(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd,
                   double offsetX, double offsetY, string color, int &stepCount, bool draw)
{
    stepCount = 0;
    QColor color_res = QColor(color.c_str());
    painter.setPen(color_res);
    double dX, dY, L;
    cnt_diff(dX, dY, L, xStart, yStart, xEnd, yEnd);
    double x = xStart, y = yStart;

    // Initialize previous integer coordinates
    int prevIntX = static_cast<int>(std::round(x));
    int prevIntY = static_cast<int>(std::round(y));

    for (int i = 0; i <= L; i++) {
        int currentIntX = static_cast<int>(std::round(x));
        int currentIntY = static_cast<int>(std::round(y));

        // Check if both coordinates changed their integer parts
        if (currentIntX != prevIntX && currentIntY != prevIntY) {
            stepCount++;
        }

        if (draw) {
            painter.drawPoint(offsetX + currentIntX, offsetY - currentIntY);
        }

        // Update previous integer coordinates
        prevIntX = currentIntX;
        prevIntY = currentIntY;

        x += dX;
        y += dY;
    }
}


void cnt_bresenham(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd,
                   double offsetX, double offsetY, string color, int &stepCount, bool draw)
{
    // 1. Ввод исходных данных
    int Xn = std::round(xStart);
    int Yn = std::round(yStart);
    int Xk = std::round(xEnd);
    int Yk = std::round(yEnd);

    // 2. Проверка вырожденности отрезка
    if (Xn == Xk && Yn == Yk) {
        if (draw) {
            painter.setPen(QColor(color.c_str()));
            painter.drawPoint(offsetX + Xn, offsetY - Yn);
        }
        return;
    }

    // 3. Вычисление приращений
    int dX = Xk - Xn;
    int dY = Yk - Yn;

    // 4. Вычисление шага изменения координат
    int SX = (dX > 0) ? 1 : -1;
    int SY = (dY > 0) ? 1 : -1;

    // 5. Вычисление модулей приращения
    dX = std::abs(dX);
    dY = std::abs(dY);

    // 6. Вычисление модуля тангенса угла наклона
    double m = (dX != 0) ? static_cast<double>(dY) / dX : 1.0;
    bool fl = false;

    // 7. Анализ m и обмен dX и dY при m > 1
    if (m > 1.0) {
        std::swap(dX, dY);
        m = 1.0 / m;
        fl = true;
    }

    // 8. Инициализация ошибки
    int f = 2 * dY - dX;

    // 9. Инициализация начальных координат
    int X = Xn;
    int Y = Yn;

    // 10. Основной цикл
    QColor color_result = QColor(color.c_str());
    int prevX = X, prevY = Y;

    // Обработка вертикального отрезка
    if (dX == 0) {
        for (int i = 0; i <= dY; i++) {
            if (draw) {
                painter.setPen(color_result);
                painter.drawPoint(offsetX + X, offsetY - Y);
            }

            // Проверка пересечения границ пикселей
            if (std::floor(X) != std::floor(prevX) && std::floor(Y) != std::floor(prevY)) {
                stepCount++;
            }

            prevX = X;
            prevY = Y;

            // Просто шагаем по оси Y
            Y += SY;
        }
        return; // Выход после вертикального отрезка
    }

    // Обработка горизонтальных и наклонных отрезков
    for (int i = 0; i <= dX; i++) {
        if (draw) {
            painter.setPen(color_result);
            painter.drawPoint(offsetX + X, offsetY - Y);
        }

        // Проверка пересечения границ пикселей
        if (std::floor(X) != std::floor(prevX) && std::floor(Y) != std::floor(prevY)) {
            stepCount++;
        }

        prevX = X;
        prevY = Y;

        // Вычисление следующей координаты
        if (f > 0) {
            if (fl) {
                X += SX;
            } else {
                Y += SY;
            }
            f -= 2 * dX;
        }

        if (fl) {
            Y += SY;
        } else {
            X += SX;
        }
        f += 2 * dY;
    }
}




void cnt_bresenham_real(QPainter &painter, double xStart, double yStart, double xEnd, double yEnd,
                        double offsetX, double offsetY, string color, int &stepCount, bool draw)
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

    // Initialize the previous values for comparison
    double prevX = x;
    double prevY = y;

    for (int i = 0; i <= dx; i++) {
        if (draw) {
            painter.setPen(color_result);
            painter.drawPoint(offsetX + x, offsetY - y);
        }

        // Check if both x and y crossed integer boundaries
        if (std::floor(x) != std::floor(prevX) && std::floor(y) != std::floor(prevY)) {
            stepCount++; // Increment step count when both coordinates cross to the next integer
        }

        // Update previous values
        prevX = x;
        prevY = y;

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
                          double offsetX, double offsetY, const std::string &color, int &stepCount, bool draw)
{
    const int I = 255; // Количество уровней интенсивности

    // 1. Ввод исходных данных
    double x1 = xStart;
    double y1 = yStart;
    double x2 = xEnd;
    double y2 = yEnd;

    // 2. Проверка вырожденности отрезка
    if (std::abs(x1 - x2) < 1e-6 && std::abs(y1 - y2) < 1e-6) {
        if (draw) {
            painter.setPen(QColor(color.c_str()));
            painter.drawPoint(offsetX + round(x1), offsetY - round(y1));
        }
        return;
    }

    // 3. Вычисление приращений
    double dx = x2 - x1;
    double dy = y2 - y1;

    // 4. Определение направления шага
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    // 5. Вычисление модулей приращений
    dx = std::abs(dx);
    dy = std::abs(dy);

    // 6. Определение основного направления
    bool steep = dy > dx;
    if (steep) {
        std::swap(dx, dy);
        std::swap(stepX, stepY);
    }

    // 7. Инициализация
    double gradient = dy / dx;
    double y = y1;
    double x = x1;

    // 8. Отрисовка первого пикселя
    if (draw) {
        double y_frac = y - std::floor(y);
        int intensity1 = std::clamp(static_cast<int>((1.0 - y_frac) * I), 0, 255);
        int intensity2 = std::clamp(static_cast<int>(y_frac * I), 0, 255);

        QColor lineColor(color.c_str());

        lineColor.setAlpha(intensity1);
        painter.setPen(lineColor);
        if (steep) {
            painter.drawPoint(offsetX + round(y), offsetY - std::floor(x));
        } else {
            painter.drawPoint(offsetX + round(x), offsetY - std::floor(y));
        }

        lineColor.setAlpha(intensity2);
        painter.setPen(lineColor);
        if (steep) {
            painter.drawPoint(offsetX + round(y), offsetY - std::ceil(x));
        } else {
            painter.drawPoint(offsetX + round(x), offsetY - std::ceil(y));
        }
    }

    double prevX = x1;
    double prevY = y1;

    // 9. Основной цикл
    for (int i = 1; i <= dx; i++) {
        x += stepX;
        y += gradient * stepY; // Исправлено: stepY вместо stepX

        // Отрисовка с антиалиасингом
        if (draw) {
            double y_frac = y - std::floor(y);
            int intensity1 = std::clamp(static_cast<int>((1.0 - y_frac) * I), 0, 255);
            int intensity2 = std::clamp(static_cast<int>(y_frac * I), 0, 255);

            QColor lineColor(color.c_str());

            lineColor.setAlpha(intensity1);
            painter.setPen(lineColor);
            if (steep) {
                painter.drawPoint(offsetX + round(y), offsetY - std::floor(x));
            } else {
                painter.drawPoint(offsetX + round(x), offsetY - std::floor(y));
            }

            lineColor.setAlpha(intensity2);
            painter.setPen(lineColor);
            if (steep) {
                painter.drawPoint(offsetX + round(y), offsetY - std::ceil(x));
            } else {
                painter.drawPoint(offsetX + round(x), offsetY - std::ceil(y));
            }
        }

        // Подсчет ступенек
        if (std::floor(x) != std::floor(prevX) && std::floor(y) != std::floor(prevY)) {
            stepCount++;
        }

        prevX = x;
        prevY = y;
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
    time_analysis.clear();
    int cnt_steps = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        cnt_steps = 0;
        xStart = lines[i].xs;
        yStart = lines[i].ys;
        xEnd = lines[i].xf;
        yEnd = lines[i].yf;

        uint64_t start = __rdtsc();

        switch (lines[i].method) {
            case DIFF:
                cnt_diff_draw(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine, cnt_steps, draw);
                break;
            case BRENZENHEM_INT:
                cnt_bresenham(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine, cnt_steps, draw);
                break;
            case BRENZENHEM_FLOAT:
                cnt_bresenham_real(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine, cnt_steps, draw);
                break;
            case BRENZENHEM_STAIR:
                bresenhamAntialiased(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine, cnt_steps, draw);
                break;
            case LIB_FUNC:
                qcolorLine = QColor(lines[i].colorLine.c_str());
                painter.setPen(qcolorLine);
                painter.drawLine(round(xStart + offset_to_center_x), round(-yStart + offset_to_center_y),
                                 round(xEnd + offset_to_center_x), round(-yEnd + offset_to_center_y));
                break;
            case WU:
                cnt_wu(painter, xStart, yStart, xEnd, yEnd, offset_to_center_x, offset_to_center_y, lines[i].colorLine, cnt_steps, draw);
                break;
            default:
                continue;
        }

        uint64_t end = __rdtsc();
        uint64_t ticks = end - start;
        cntSteps.push_back(cnt_steps);
        time_analysis.push_back(static_cast<double>(ticks));
        draw = true;
    }


    Q_UNUSED(event);
}



