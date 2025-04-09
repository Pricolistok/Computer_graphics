from drawpixel import drawSimPixels
import math as m


def parameter_circle(canvas, xc, yc, r, draw):
    step = 1 / r

    i = 0
    while i <= m.pi / 4 + step:
        x = xc + r * m.cos(i)
        y = yc + r * m.sin(i)

        if draw:
            drawSimPixels(canvas, [x, y], xc, yc, circle=True)

        i += step


def parameter_ellipse(canvas, xc, yc, ra, rb, draw):
    if ra > rb:
        step = 1 / ra
    else:
        step = 1 / rb

    i = 0
    while i <= m.pi / 2 + step:
        x = xc + round(ra * m.cos(i))
        y = yc + round(rb * m.sin(i))

        if draw:
            drawSimPixels(canvas, [x, y], xc, yc, circle=False)

        i += step
