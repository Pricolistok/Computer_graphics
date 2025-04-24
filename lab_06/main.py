import sys
from PyQt5.QtCore import Qt, pyqtSignal, QPoint, QRect
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox, QButtonGroup, QRadioButton, QLabel
from design import Ui_MainWindow
from consts import *
from errors import *
from dataclasses import dataclass



@dataclass
class Point:
    x: int
    y: int


@dataclass
class SeedPoint:
    point: Point
    color: str

@dataclass
class Figure:
    dots: list[Point]


@dataclass
class Circle:
    center: Point
    radius: int


@dataclass
class Ellipse:
    center: Point
    radiusX: int
    radiusY: int


def checkIntNum(*args):
    error_code = OK
    array_result = [error_code]
    try:
        for i in args:
            array_result.append(int(i))
    except ValueError:
        array_result[-1] = 0
        array_result[0] = ERROR_INPUT_DATA
    return array_result


class CanvasLabel(QLabel):
    clickedLeft = pyqtSignal(QPoint)
    clickedRight = pyqtSignal(QPoint)
    clickedMiddle = pyqtSignal(QPoint)
    draggedLeft = pyqtSignal(QPoint)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMouseTracking(True)
        self.left_button_pressed = False

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.left_button_pressed = True
            self.clickedLeft.emit(event.pos())
        elif event.button() == Qt.RightButton:
            self.clickedRight.emit(event.pos())
        elif event.button() == Qt.MiddleButton:
            self.clickedMiddle.emit(event.pos())

    def mouseMoveEvent(self, event):
        if self.left_button_pressed:
            self.draggedLeft.emit(event.pos())

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.left_button_pressed = False




class MainApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pixMap = None

        self.colorBG = 'black'
        self.colorBorder = 'white'
        self.colorShading = 'red'
        self.dataset_figures = []
        self.dataset_circles = []
        self.dataset_ellipses = []
        self.dotsSeed = []
        self.button_group = QButtonGroup()
        self.mode_delay = 1
        self.mode_draw = None

        self.tmp_dots_array = []

        self.initConnections()
        self.initQPainter()
        self.initDesign()
        self.initRadioButton()
        self.initMouse()

    def initQPainter(self):
        self.canvas.setParent(None)
        self.canvas.deleteLater()

        self.canvas = CanvasLabel(self)
        self.canvas.setGeometry(CANVAS_MARGIN_X, CANVAS_MARGIN_Y, WIDTH_CANVAS, HEIGHT_CANVAS)
        self.canvas.setObjectName("canvas")
        self.pixMap = QPixmap(WIDTH_CANVAS, HEIGHT_CANVAS)
        self.canvas.setPixmap(self.pixMap)
        self.canvas.setParent(self.centralwidget)
        self.canvas.show()

    def initMouse(self):
        self.canvas.clickedLeft.connect(self.onCanvasLeftClick)
        self.canvas.clickedRight.connect(self.onCanvasRightClick)
        self.canvas.clickedMiddle.connect(self.onCanvasMiddleClick)
        self.canvas.draggedLeft.connect(self.onCanvasLeftDragged)

    def onCanvasLeftClick(self, pos):
        self.tmp_dots_array.append(Point(pos.x(), pos.y()))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()

    def onCanvasRightClick(self, pos):
        self.tmp_dots_array.append(self.tmp_dots_array[0])
        array = self.tmp_dots_array.copy()
        self.dataset_figures.append(Figure(dots=array))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()
        self.tmp_dots_array.clear()

    def onCanvasLeftDragged(self, pos):
        self.tmp_dots_array.append(Point(pos.x(), pos.y()))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()

    def onCanvasMiddleClick(self, pos):
        self.dotsSeed.append(SeedPoint(Point(pos.x(), pos.y()), self.colorShading))

    def initRadioButton(self):
        self.radioButtonNoDelay.setChecked(True)
        self.button_group = QButtonGroup()
        self.button_group.addButton(self.radioButtonDelay)
        self.button_group.addButton(self.radioButtonNoDelay)
        self.button_group.buttonClicked.connect(self.eventRadioButton)


    def eventRadioButton(self, button: QRadioButton):
        if button.text() == 'С задержкой':
            self.mode_delay = 0
        else:
            self.mode_delay = 1


    def initConnections(self):
        self.pushButtonClearCanvas.clicked.connect(self.eventCleanCanvas)
        self.pushButtonColorBG.clicked.connect(self.eventChooseColorBG)
        self.pushButtonColorBorder.clicked.connect(self.eventChooseColorBorder)
        self.pushButtonColorFigure.clicked.connect(self.eventChooseColorShading)
        self.pushButtonCreateCircle.clicked.connect(self.eventCreateCircle)
        self.pushButtonCreateEllipse.clicked.connect(self.eventCreateEllipse)
        self.pushButtonCreateDot.clicked.connect(self.eventCreateDot)
        self.pushButtonCreateFigure.clicked.connect(self.eventCreateFigure)
        self.pushButtonCreateSeed.clicked.connect(self.eventCreateSeed)
        self.pushButtonShading.clicked.connect(self.eventShading)



    def initDesign(self):
        self.pixMap.fill(QColor(self.colorBG))
        self.pushButtonColorBG.setStyleSheet(f"background-color: {self.colorBG}")
        self.pushButtonColorFigure.setStyleSheet(f"background-color: {self.colorShading}")
        self.pushButtonColorBorder.setStyleSheet(f"background-color: {self.colorBorder}")



    def eventCleaner(self):
        pass

    def eventChooseColorBG(self):
        self.colorBG = self.eventChooseColor()
        self.pixMap.fill(QColor(self.colorBG))
        self.canvas.setPixmap(self.pixMap)
        self.pushButtonColorBG.setStyleSheet(f"background-color: {self.colorBG}")
        # self.paint()

    def eventChooseColorShading(self):
        self.colorShading = self.eventChooseColor()
        self.pushButtonColorFigure.setStyleSheet(f"background-color: {self.colorShading}")

    def eventChooseColorBorder(self):
        self.colorBorder = self.eventChooseColor()
        self.pushButtonColorBorder.setStyleSheet(f"background-color: {self.colorBorder}")

    def eventCreateCircle(self):
        self.addCircle()
        self.paint()

    def eventCreateEllipse(self):
        self.addEllipse()
        self.paint()

    def eventCreateDot(self):
        self.addDotCoords()
        self.paint()

    def eventCreateFigure(self):
        self.addFigure()

    def eventCreateSeed(self):
        self.addDotSeed()

    def eventShading(self):
        pass


    @staticmethod
    def eventChooseColor():
        return QColorDialog.getColor().name()


    @staticmethod
    def senderErrorMessage(text):
        message = QMessageBox()
        message.setWindowTitle("Ошибка")
        message.setText(text)
        message.exec_()

    def addDotCoords(self):
        tmp_x = self.lineEditLineCreatorX.text()
        tmp_y = self.lineEditLineCreatorY.text()
        array_result = checkIntNum(tmp_x, tmp_y)
        if array_result[0] == OK:
            point = Point(array_result[1], array_result[2])
            self.tmp_dots_array.append(point)
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения точки!")
        self.mode_draw = Methods.MODE_DRAW_FIGURE

    def addDotSeed(self):
        tmp_x = self.lineEditLineCreatorX.text()
        tmp_y = self.lineEditLineCreatorY.text()
        array_result = checkIntNum(tmp_x, tmp_y)
        if array_result[0] == OK:
            seed_point = SeedPoint(Point(array_result[1], array_result[2]), self.colorShading)
            self.dotsSeed.append(seed_point)
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения точки затравки!")
        print(self.dotsSeed)

    def addFigure(self):
        self.tmp_dots_array.append(self.tmp_dots_array[0])
        array = self.tmp_dots_array.copy()
        self.dataset_figures.append(Figure(dots=array))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()
        self.tmp_dots_array.clear()

    def addCircle(self):
        tmp_cx = self.lineEditXC.text()
        tmp_cy = self.lineEditYC.text()
        tmp_r = self.lineEditR.text()
        array_result = checkIntNum(tmp_cx, tmp_cy, tmp_r)
        if array_result[0] == OK:
            if array_result[3] > 0:
                point = Point(array_result[1], array_result[2])
                circle = Circle(point, array_result[3])
                self.dataset_circles.append(circle)
            else:
                self.senderErrorMessage("Ошибка при вводе значений построения окружности!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения окружности!")
        self.mode_draw = Methods.MODE_DRAW_CIRCLE
        self.paint()


    def addEllipse(self):
        tmp_cx = self.lineEditXC.text()
        tmp_cy = self.lineEditYC.text()
        tmp_rx = self.lineEditRX.text()
        tmp_ry = self.lineEditRY.text()
        array_result = checkIntNum(tmp_cx, tmp_cy, tmp_rx, tmp_ry)
        if array_result[0] == OK:
            if array_result[3] > 0 and array_result[4] > 0:
                point = Point(array_result[1], array_result[2])
                ellipse = Ellipse(point, array_result[3], array_result[4])
                self.dataset_ellipses.append(ellipse)
            else:
                self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")
        self.mode_draw = Methods.MODE_DRAW_ELLIPSE
        self.paint()


    def eventCleanCanvas(self):
        self.initQPainter()
        self.dataset_figures.clear()
        self.dataset_circles.clear()
        self.dataset_ellipses.clear()
        self.tmp_dots_array.clear()
        self.initDesign()
        self.mode_draw = Methods.MODE_DRAW_CLEAR
        self.paint()


    def paint(self):
        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorBorder))
        painter.setPen(pen)

        match self.mode_draw:
            case Methods.MODE_DRAW_FIGURE:
                if len(self.tmp_dots_array) > 1:
                    painter.drawLine(self.tmp_dots_array[-2].x, self.tmp_dots_array[-2].y, self.tmp_dots_array[-1].x, self.tmp_dots_array[-1].y)
            case Methods.MODE_DRAW_SEED:
                pass
            case Methods.MODE_DRAW_ELLIPSE:
                painter.drawEllipse(QRect((self.dataset_ellipses[-1].center.x - self.dataset_ellipses[-1].radiusX), (self.dataset_ellipses[-1].center.y - self.dataset_ellipses[-1].radiusY),
                                           self.dataset_ellipses[-1].radiusX * 2, self.dataset_ellipses[-1].radiusY * 2))

            case Methods.MODE_DRAW_CIRCLE:
                painter.drawEllipse(QRect((self.dataset_circles[-1].center.x - self.dataset_circles[-1].radius), (self.dataset_circles[-1].center.y - self.dataset_circles[-1].radius),
                                           self.dataset_circles[-1].radius * 2, self.dataset_circles[-1].radius * 2))
            case Methods.MODE_DRAW_CLEAR:
                self.canvas.repaint()
            case _:
                pass
        self.canvas.update()


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
