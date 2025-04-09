from PyQt5.QtCore import QRectF
from consts import *
from bresenhem import *
from canonical import *
from param import *
from middle import *
from PyQt5.QtGui import QColor


def mainPainter(painter, pen, data: Ellipsis, draw_mode=True):
    pen.setColor(QColor(data.color))
    painter.setPen(pen)
    if data.rx == data.ry:
        match data.method:
            case Methods.METHOD_LIB:
                print('Lib')
                painter.drawEllipse(QRectF((data.cx - data.rx) + X_OFFSET, Y_OFFSET - (data.cy + data.ry),
                                           data.rx * 2, data.ry * 2))
            case Methods.METHOD_CANONICAL:
                print("Canonical")
                canonicalCircle(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, draw_mode)
            case Methods.METHOD_PARAM:
                print("Param")
                parameter_circle(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, draw_mode)
            case Methods.METHOD_AVERAGE:
                print('Middle')
                midpoint_circle(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, draw_mode)
            case Methods.METHOD_BRESENHAM:
                print('Bresenham')
                bresenham_circle_octant(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, draw_mode)

    else:
        match data.method:
            case Methods.METHOD_LIB:
                print('Lib')
                painter.drawEllipse(QRectF((data.cx - data.rx) + X_OFFSET, Y_OFFSET - (data.cy + data.ry),
                                           data.rx * 2, data.ry * 2))
            case Methods.METHOD_CANONICAL:
                print("Canonical")
                canonical_ellipse(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, data.ry, draw_mode)
            case Methods.METHOD_PARAM:
                print("Param")
                parameter_ellipse(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, data.ry, draw_mode)
            case Methods.METHOD_AVERAGE:
                print('Middle')
                midpoint_ellipse(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, data.ry, draw_mode)
            case Methods.METHOD_BRESENHAM:
                print('Bresenham')
                bresenham_ellipse(painter, data.cx + X_OFFSET, Y_OFFSET - data.cy, data.rx, data.ry, draw_mode)

