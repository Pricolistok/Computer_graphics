#include "maindrawer.h"
#include <QColor>

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QColor qcolorLine;
    qcolorLine = QColor(colorLine.c_str());
    painter.setPen(qcolorLine);

    double offset_to_center_x = WIDTH_CANVAS / 2, offset_to_center_y = HEIGHT_CANVAS / 2;
    painter.drawLine(offset_to_center_x + line.xs, offset_to_center_y - line.ys,
                     offset_to_center_x + line.xf,offset_to_center_y - line.yf);
    Q_UNUSED(event);
}
