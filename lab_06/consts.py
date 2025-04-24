from dataclasses import dataclass

WIDTH_CANVAS = 850
HEIGHT_CANVAS = 700
CANVAS_MARGIN_X = 350
CANVAS_MARGIN_Y = 40
ERROR = 400
OK = 1


class Methods:
    MODE_DRAW_FIGURE: int = 100
    MODE_DRAW_SEED: int = 200
    MODE_DRAW_CIRCLE: int = 300
    MODE_DRAW_ELLIPSE: int = 400
    MODE_DRAW_CLEAR: int = 500