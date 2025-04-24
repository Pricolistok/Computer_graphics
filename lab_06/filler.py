from consts import *
from PyQt5.QtGui import QPainter, QColor, QImage
from dataclasses import dataclass
from PyQt5.QtWidgets import QApplication

@dataclass
class Point:
    x: int
    y: int

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

def line_by_line_filling_algorithm_with_seed(painter: QPainter, canvas, pixmap, border_colour, fill_colour, seed_point, delay=False):
    fill_colour_q = QColor(fill_colour)
    border_colour_q = QColor(border_colour)
    fill_colour_rgb = fill_colour_q.rgb()
    border_colour_rgb = border_colour_q.rgb()

    print("fill_c =", fill_colour_q, fill_colour_rgb)
    print("border_c =", border_colour_q, border_colour_rgb)

    # Создаём копию изображения для чтения цветов и ручной синхронизации
    image = pixmap.toImage().convertToFormat(QImage.Format_RGB32)

    def get_color(x, y):
        return image.pixelColor(x, y).rgb()

    def set_color(x, y, color):
        painter.setPen(QColor(color))
        painter.drawPoint(x, y)
        image.setPixelColor(x, y, QColor(color))  # Обновляем изображение вручную

    stack = [seed_point]

    while stack:
        seed_pixel = stack.pop()
        x = seed_pixel.x
        y = seed_pixel.y

        print(f"Processing pixel at ({x}, {y})")

        if not (0 <= x < WIDTH_CANVAS and 0 <= y < HEIGHT_CANVAS):
            print(f"Out of bounds: ({x}, {y})")
            continue

        # Если уже закрашено или граница — пропускаем
        if get_color(x, y) in [fill_colour_rgb, border_colour_rgb]:
            continue

        # Рисуем пиксель и запоминаем исходные координаты
        set_color(x, y, fill_colour_rgb)
        tx = x
        ty = y

        # Справа от затравки
        x += 1
        while x < WIDTH_CANVAS and get_color(x, y) not in [fill_colour_rgb, border_colour_rgb]:
            set_color(x, y, fill_colour_rgb)
            x += 1
        xr = x - 1

        # Слева от затравки
        x = tx - 1
        while x >= 0 and get_color(x, y) not in [fill_colour_rgb, border_colour_rgb]:
            set_color(x, y, fill_colour_rgb)
            x -= 1
        xl = x + 1

        # Верхняя строка
        if ty + 1 < HEIGHT_CANVAS:
            y_next = ty + 1
            x = xl
            while x <= xr:
                flag = False
                while x <= xr and get_color(x, y_next) not in [fill_colour_rgb, border_colour_rgb]:
                    flag = True
                    x += 1
                if flag:
                    stack.append(Point(x - 1, y_next))
                while x <= xr and get_color(x, y_next) in [fill_colour_rgb, border_colour_rgb]:
                    x += 1

        # Нижняя строка
        if ty - 1 >= 0:
            y_prev = ty - 1
            x = xl
            while x <= xr:
                flag = False
                while x <= xr and get_color(x, y_prev) not in [fill_colour_rgb, border_colour_rgb]:
                    flag = True
                    x += 1
                if flag:
                    stack.append(Point(x - 1, y_prev))
                while x <= xr and get_color(x, y_prev) in [fill_colour_rgb, border_colour_rgb]:
                    x += 1

        if delay:
            canvas.update()
            QApplication.processEvents()

    canvas.update()
