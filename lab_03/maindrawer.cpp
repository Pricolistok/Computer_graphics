#include "maindrawer.h"

MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{

}

void MyDrawWidget::paintEvent(QPaintEvent *event)
{
    double offset_to_center_x = WIDTH_CANVAS / 2, offset_to_center_y = HEIGHT_CANVAS / 2;
    QPainter painter(this);
    painter.drawLine(offset_to_center_x + line.xs, offset_to_center_y - line.ys,
                     offset_to_center_x + line.xf,offset_to_center_y - line.yf);
    Q_UNUSED(event);
    painter.setPen(Qt::white);
}
