from PyQt5.QtGui import QPainter
from PyQt5.QtCore import QPointF


def set_pixel(canvas:QPainter, x, y):
    canvas.drawPoint(QPointF(x, y))


def drawSimPixels(canvas, dot, xc, yc, circle=True):
    if circle:
        set_pixel(canvas,  dot[1] - yc + xc,  dot[0] - xc + yc)
        set_pixel(canvas, -dot[1] + yc + xc,  dot[0] - xc + yc)
        set_pixel(canvas,  dot[1] - yc + xc, -dot[0] + xc + yc)
        set_pixel(canvas, -dot[1] + yc + xc, -dot[0] + xc + yc)

    set_pixel(canvas,  dot[0],           dot[1])
    set_pixel(canvas, -dot[0] + 2 * xc,  dot[1])
    set_pixel(canvas,  dot[0],          -dot[1] + 2 * yc)
    set_pixel(canvas, -dot[0] + 2 * xc, -dot[1] + 2 * yc)