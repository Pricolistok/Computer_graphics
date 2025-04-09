from PyQt5.QtCore import QRectF

import consts
from consts import *
from PyQt5.QtGui import QColor


def mainPainter(painter, pen, data: Ellipsis):
    pen.setColor(QColor(data.color))
    painter.setPen(pen)
    match data.method:
        case Methods.METHOD_LIB:
            painter.drawEllipse(QRectF((data.cx - data.rx) + X_OFFSET, Y_OFFSET - (data.cy + data.ry),
                                       data.rx * 2, data.ry * 2))
        case Methods.METHOD_CANONICAL:
            print('jk')
        case Methods.METHOD_PARAM:
            print('jk')
        case Methods.METHOD_AVERAGE:
            print('jk')
        case Methods.METHOD_BRESENHAM:
            print('jk')

    painter.drawEllipse(rect)
