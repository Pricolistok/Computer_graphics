import sys
from PyQt5.QtCore import Qt, pyqtSignal, QPoint, QRect
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox, QButtonGroup, QRadioButton, QLabel
from design import Ui_MainWindow
from consts import *
from errors import *
from ellipses import Ellipse
from dataclasses import dataclass


@dataclass
class Point:
    x: int
    y: int


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
    radiusX = int
    radiusY: int



def checkFloatNum(*args):
    error_code = OK
    array_result = [error_code]
    try:
        for i in args:
            array_result.append(float(i))
    except ValueError:
        array_result[-1] = 0
        array_result[0] = ERROR_INPUT_DATA
    return array_result


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

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMouseTracking(True)

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.clickedLeft.emit(event.pos())
        elif event.button() == Qt.RightButton:
            self.clickedRight.emit(event.pos())
        elif event.button() == Qt.MiddleButton:
            self.clickedMiddle.emit(event.pos())



class MainApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pixMap = None

        self.colorBG = 'black'
        self.colorBorder = 'white'
        self.colorShading = 'red'
        self.dataset = []
        self.dotsSeed = []
        self.button_group = QButtonGroup()
        self.mode_delay = 1

        self.ellipses = []
        self.tmp_dots_array = []

        self.initConnections()
        self.initQPainter()
        self.initDesign()
        self.initRadioButton()

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

        self.canvas.clickedLeft.connect(self.onCanvasLeftClick)
        self.canvas.clickedRight.connect(self.onCanvasRightClick)
        self.canvas.clickedMiddle.connect(self.onCanvasMiddleClick)

    def onCanvasLeftClick(self, pos):
        self.tmp_dots_array.append(Point(pos.x(), pos.y()))

    def onCanvasRightClick(self, pos):
        array = self.tmp_dots_array.copy()
        self.dataset.append(Figure(dots=array))
        self.paint()

    def onCanvasMiddleClick(self, pos):
        self.dotsSeed.append(Point(pos.x(), pos.y()))

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
        self.pushButtonClearCanvas.clicked.connect(self.eventCleaner)
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
        pass

    def eventCreateEllipse(self):
        pass

    def eventCreateDot(self):
        pass

    def eventCreateFigure(self):
        pass

    def eventCreateSeed(self):
        pass

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


    def eventAddCircle(self):
        self.addCircle()
        self.paint()


    def addCircle(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_r = self.lineEditCircleR.text()
        array_result = checkFloatNum(tmp_cx, tmp_cy, tmp_r)
        if array_result[0] == OK:
            if array_result[3] > 0:
                ellipse = Ellipse(array_result[1], array_result[2], array_result[3], array_result[3], self.colorPen, self.method)
                self.ellipses.append(ellipse)
            else:
                self.senderErrorMessage("Ошибка при вводе значений построения круга!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения круга!")


    def eventAddEllipse(self):
        self.addEllipse()
        self.paint()


    def addEllipse(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_rx = self.lineEditElipseH.text()
        tmp_ry = self.lineEditElipseW.text()
        array_result = checkFloatNum(tmp_cx, tmp_cy, tmp_rx, tmp_ry)
        if array_result[0] == OK:
            if array_result[3] > 0 and array_result[4] > 0:
                ellipse = Ellipse(array_result[1], array_result[2], array_result[3], array_result[4], self.colorPen, self.method)
                self.ellipses.append(ellipse)
            else:
                self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")



    def eventCleanCanvas(self):
        self.ellipses.clear()
        self.initQPainter()
        self.colorBG = 'black'
        self.colorBorder = 'white'
        self.initDesign()
        self.paint()


    def paint(self):
        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorBorder))
        painter.setPen(pen)
        for i in range(len(self.dataset) - 1):
            if type(self.dataset[i]) == Figure:
                if len(self.dataset[i].dots) > 1:
                    print("JJJJ")
                    print(len(self.dataset[i].dots))
                    for j in range(len(self.dataset[i].dots) - 1):
                        painter.drawLine(self.dataset[i].dots[j].x, self.dataset[i].dots[j].y, self.dataset[i].dots[j + 1].x, self.dataset[i].dots[j + 1].y)
        self.canvas.repaint()


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
