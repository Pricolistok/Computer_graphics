from drawpixel import drawSimPixels
import math as m


def canonicalCircle(canvas, xc, yc, r, draw):
    sqr_r = r ** 2

    border = round(xc + r / m.sqrt(2))

    for x in range(round(xc), border + 1):
        y = yc + m.sqrt(sqr_r - (x - xc) ** 2)
        if draw:
            drawSimPixels(canvas, [x, y], xc, yc, circle=True)


def canonical_ellipse(canvas, xc, yc, ra, rb, draw):
    sqr_ra = ra * ra
    sqr_rb = rb * rb

    border_x = round(xc + ra / m.sqrt(1 + sqr_rb / sqr_ra))
    border_y = round(yc + rb / m.sqrt(1 + sqr_ra / sqr_rb))

    for x in range(round(xc), border_x + 1):
        y = yc + m.sqrt(sqr_ra * sqr_rb - (x - xc) ** 2 * sqr_rb) / ra

        if draw:
            drawSimPixels(canvas, [x, y], xc, yc, circle=False)

    for y in range(border_y, round(yc) - 1, -1):
        x = xc + m.sqrt(sqr_ra * sqr_rb - (y - yc) ** 2 * sqr_ra) / rb

        if draw:
            drawSimPixels(canvas, [x, y], xc, yc, circle=False)