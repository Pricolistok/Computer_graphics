import sys
from PyQt5.QtCore import Qt, pyqtSignal, QPoint, QRect
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap, QIcon
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox, QButtonGroup, QRadioButton, QLabel
from design import Ui_MainWindow
from consts import *
from errors import *
from brezenhem import *
from filler import line_by_line_filling_algorithm_with_seed
from time import time

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
        self.setWindowTitle('CG lab_06')
        self.setWindowIcon(QIcon('icon.ico'))

        self.colorBG = 'black'
        self.colorBorder = 'white'
        self.colorShading = 'red'
        self.dataset_figures = []
        self.dataset_circles = []
        self.dataset_ellipses = []
        self.dotsSeed = []
        self.allPoints: list[Point] = []
        self.button_group = QButtonGroup()
        self.mode_delay = 1
        self.mode_draw = None

        self.tmp_dots_array = []

        self.initConnections()
        self.initQPainter()
        self.initDesign()
        self.initRadioButton()
        self.initMouse()
        self.plainTextEditData.appendPlainText("_____START_____")

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
        self.appendLog('X: {:>6d} Y: {:>6d}'.format(pos.x(), pos.y()))

    def onCanvasRightClick(self, pos):
        if len(self.tmp_dots_array) < 2:
            self.senderErrorMessage('Ошибка, фигура не может быть замкнута!')
            return
        self.tmp_dots_array.append(self.tmp_dots_array[0])
        array = self.tmp_dots_array.copy()
        self.dataset_figures.append(Figure(dots=array))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()
        self.allPoints += self.tmp_dots_array
        self.tmp_dots_array.clear()
        self.appendLog('____CLOSED____')

    def onCanvasLeftDragged(self, pos):
        self.tmp_dots_array.append(Point(pos.x(), pos.y()))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()
        self.appendLog('X: {:>6d} Y: {:>6d}'.format(pos.x(), pos.y()))

    def onCanvasMiddleClick(self, pos):
        self.dotsSeed.append(SeedPoint(Point(pos.x(), pos.y()), self.colorShading))
        self.eventShading()
        self.appendLog('Seed Point')
        self.appendLog('X: {:>6d} Y: {:>6d}'.format(pos.x(), pos.y()))
        self.appendLog('____CLOSED____')

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
        self.plainTextEditData.setReadOnly(True)
        self.plainTextEditData.setStyleSheet("background-color: white")
        self.pushButtonColorBorder.setStyleSheet(f"background-color: {self.colorBorder}")

    def appendLog(self, text: str):
        self.plainTextEditData.appendPlainText(text)
        scrollbar = self.plainTextEditData.verticalScrollBar()
        scrollbar.setValue(scrollbar.maximum())

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

    def checkerFigures(self):
        for i in self.dataset_figures:
            if i[0] != i[-1]:
                return ERROR
        return OK

    def eventShading(self):
        print(self.dotsSeed)
        if not self.dataset_figures and not self.dataset_circles and not self.dataset_ellipses and not self.tmp_dots_array:
            self.senderErrorMessage("Фигура не введена для закраски!")
            return
        if not self.dotsSeed:
            self.senderErrorMessage("Затравочный пиксел не установлен!")
            return
        if self.colorBorder == self.colorShading:
            self.senderErrorMessage("Цвет границы и цвет закраски не должны совпадать!")
            return
        if self.colorBG == self.colorBorder:
            self.senderErrorMessage("Цвет границы и цвет фона не должны совпадать!")
            return
        if self.colorBG == self.colorShading:
            self.senderErrorMessage("Цвет фона и цвет закраски не должны совпадать!")
            return

        delay = not self.mode_delay
        last_seed = self.dotsSeed[-1].point

        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorShading))
        painter.setPen(pen)
        from filler import Point as SeedPointClass
        try:
            start = time()
            line_by_line_filling_algorithm_with_seed(
                painter,
                self.canvas,
                self.canvas.pixmap(),
                self.colorBorder,
                self.colorShading,
                SeedPointClass(last_seed.x, last_seed.y),
                delay,
            )
            finish = time()
            self.labelTime.setText('Время закраски: {:7.5f}c'.format(finish - start))
        except Exception as e:
            import traceback
            print("Ошибка при выполнении закраски:")
            traceback.print_exc()
            self.senderErrorMessage(f"Ошибка: {e}")

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
            return
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.appendLog('X: {:>6d} Y: {:>6d}'.format(array_result[1], array_result[2]))

    def addDotSeed(self):
        tmp_x = self.lineEditLineCreatorX.text()
        tmp_y = self.lineEditLineCreatorY.text()
        array_result = checkIntNum(tmp_x, tmp_y)
        if array_result[0] == OK:
            seed_point = SeedPoint(Point(array_result[1], array_result[2]), self.colorShading)
            self.dotsSeed.append(seed_point)
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения точки затравки!")
            return
        self.appendLog('Seed Point')
        self.appendLog('X: {:>6d} Y: {:>6d}'.format(array_result[1], array_result[2]))
        self.appendLog('____CLOSED____')

    def addFigure(self):
        if len(self.tmp_dots_array) < 2:
            self.senderErrorMessage('Ошибка, фигура не может быть замкнута!')
            return
        self.tmp_dots_array.append(self.tmp_dots_array[0])
        array = self.tmp_dots_array.copy()
        self.dataset_figures.append(Figure(dots=array))
        self.mode_draw = Methods.MODE_DRAW_FIGURE
        self.paint()
        self.allPoints += self.tmp_dots_array
        self.tmp_dots_array.clear()
        self.appendLog('____CLOSED____')

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
                return
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения окружности!")
            return
        self.mode_draw = Methods.MODE_DRAW_CIRCLE
        self.paint()
        points = bresenham_circle(array_result[1], array_result[2], array_result[3])
        self.allPoints += points
        self.appendLog('CIRCLE')
        self.appendLog('XC: {:>6d} YC: {:>6d}'.format(array_result[1], array_result[2]))
        self.appendLog('RX: {:>6d}'.format(array_result[3]))
        self.appendLog('____CLOSED____')


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
                return
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")
            return
        self.mode_draw = Methods.MODE_DRAW_ELLIPSE
        self.paint()
        points = bresenham_ellipse(array_result[1], array_result[2], array_result[3], array_result[4])
        self.allPoints += points
        self.appendLog('ELLIPSE')
        self.appendLog('XC: {:>6d} YC: {:>6d}'.format(array_result[1], array_result[2]))
        self.appendLog('RX: {:>6d} RY: {:>6d}'.format(array_result[3], array_result[4]))
        self.appendLog('____CLOSED____')

    def eventCleanCanvas(self):
        self.initQPainter()
        self.dataset_figures.clear()
        self.dataset_circles.clear()
        self.dataset_ellipses.clear()
        self.tmp_dots_array.clear()
        self.dotsSeed.clear()
        self.initDesign()
        self.allPoints.clear()
        self.mode_draw = Methods.MODE_DRAW_CLEAR
        self.initMouse()
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
