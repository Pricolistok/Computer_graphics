import matplotlib.pyplot as plt
import numpy as np


class DatasetCircle:
    # lib_func = []
    canonical = []
    param = []
    middle = []
    bresenham = []
    radius = []


class DatasetEllipse:
    # lib_func = []
    canonical = []
    param = []
    middle = []
    bresenham = []
    radius = []


def create_one_graphic(canonical, param, middle, bresenham, len_circle, title, name, step=10):
    """
    Параметры:
    - step: шаг, с которым берутся точки из массивов (по умолчанию 10).
    """
    plt.figure(figsize=(10, 6))
    plt.xlabel('Длина радиуса')
    plt.ylabel('Время в секундах')
    plt.title(title)

    # Берём только каждую step-ую точку из массивов
    len_circle_thinned = len_circle[::step]
    canonical_thinned = canonical[::step]
    param_thinned = param[::step]
    middle_thinned = middle[::step]
    bresenham_thinned = bresenham[::step]

    # Строим графики по прореженным данным
    plt.plot(
        len_circle_thinned, canonical_thinned,
        linestyle='-', color='blue', markersize=5, label="Каноническое уравнение"
    )
    plt.plot(
        len_circle_thinned, param_thinned,
        linestyle='-', color='red', markersize=5, label="Параметрическое уравнение"
    )
    plt.plot(
        len_circle_thinned, middle_thinned,
        linestyle='-', color='green', markersize=5, label="Алгоритм средней точки"
    )
    plt.plot(
        len_circle_thinned, bresenham_thinned,
        linestyle='-', color='purple', markersize=5, label="Алгоритм Брезенхема"
    )

    plt.legend()
    plt.xticks(len_circle_thinned)  # Подписи оси X тоже прореживаем
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.savefig(f"pictures/{name}")
    plt.show()


def creatorGraphics(circle: DatasetCircle(), ellipse: DatasetEllipse()):
    create_one_graphic(circle.canonical, circle.param, circle.middle, circle.bresenham, circle.radius,
                       'Замеры для построения окружности.', "circle")
    create_one_graphic(ellipse.canonical, ellipse.param, ellipse.middle, ellipse.bresenham, ellipse.radius,
                       'Замеры для построения эллипса.', "ellipse")

