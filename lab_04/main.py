import sys
from timeanalysis import *
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox
from design import Ui_MainWindow
from consts import *
from errors import *
from ellipses import Ellipse
from maindrawer import mainPainter
from time import time
from math import pi


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


class MainApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.pixMap = None

        self.colorBG = 'black'
        self.colorPen = 'white'
        self.method = Methods.METHOD_LIB

        self.ellipses = []

        self.time_circle = DatasetCircle()
        self.time_ellipse = DatasetEllipse()

        self.initConnections()
        self.initQPainter()
        self.initDesign()


    def initQPainter(self):
        self.pixMap = QPixmap(WIDTH_CANVAS, HEIGHT_CANVAS)
        self.canvas.setPixmap(self.pixMap)


    def initConnections(self):
        self.pushButtonColorBG.clicked.connect(self.changeColorBG)
        self.pushButtonColorCircle.clicked.connect(self.changeColorCircle)
        self.pushButtonDrawCircle.clicked.connect(self.eventAddCircle)
        self.pushButtonDrawEllipse.clicked.connect(self.eventAddEllipse)
        self.pushButtonDrawSpectorCircle.clicked.connect(self.eventAddSpectorCircle)
        self.pushButtonDrawSpectorEllipse.clicked.connect(self.eventAddSpectorEllipse)
        self.pushButtonClear.clicked.connect(self.eventCleanCanvas)
        self.pushButtonData.clicked.connect(self.createDataset)
        self.comboBox.activated.connect(self.eventSetMethod)

    def createDataset(self):
        self.time_ellipse.param.clear()
        self.time_ellipse.canonical.clear()
        self.time_ellipse.bresenham.clear()
        self.time_ellipse.middle.clear()
        self.time_ellipse.radius.clear()

        self.time_circle.param.clear()
        self.time_circle.canonical.clear()
        self.time_circle.bresenham.clear()
        self.time_circle.middle.clear()
        self.time_circle.radius.clear()

        min_radius = 100
        max_radius = 10000
        step = 100

        self.pixMap = QPixmap(WIDTH_CANVAS, HEIGHT_CANVAS)
        self.canvas.setPixmap(self.pixMap)

        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorPen))
        painter.setPen(pen)

        self.createDatasetCircle(min_radius, max_radius, step, painter, pen)
        self.createDatasetEllipse(min_radius, max_radius, step, painter, pen)

        painter.end()
        self.canvas.repaint()

        creatorGraphics(self.time_circle, self.time_ellipse)


    def createDatasetCircle(self, min_radius, max_radius, step, painter, pen):

        for radius in range(min_radius, max_radius, step):
            # start = datetime.now()
            # mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_LIB), False)
            # finish = datetime.now()
            # self.time_circle.lib_func.append(start - finish)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_CANONICAL),
                        False)
            finish = time()
            self.time_circle.canonical.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_PARAM),
                        False)
            finish = time()
            self.time_circle.param.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_AVERAGE),
                        False)
            finish = time()
            self.time_circle.middle.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_BRESENHAM),
                        False)
            finish = time()
            self.time_circle.bresenham.append((finish - start) * 1_000)

            self.time_circle.radius.append(radius)


    def createDatasetEllipse(self, min_radius, max_radius, step, painter, pen):
        for radius in range(min_radius, max_radius, step):
            # start = datetime.now()
            # mainPainter(painter, pen, Ellipse(0, 0, radius, radius, self.colorPen, Methods.METHOD_LIB), False)
            # finish = datetime.now()
            # self.time_ellipse.lib_func.append(start - finish)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius + 20, self.colorPen, Methods.METHOD_CANONICAL),
                        False)
            finish = time()
            self.time_ellipse.canonical.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius + 20, self.colorPen, Methods.METHOD_PARAM),
                        False)
            finish = time()
            self.time_ellipse.param.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius + 20, self.colorPen, Methods.METHOD_AVERAGE),
                        False)
            finish = time()
            self.time_ellipse.middle.append((finish - start) * 1_000)

            start = time()
            mainPainter(painter, pen, Ellipse(0, 0, radius, radius + 20, self.colorPen, Methods.METHOD_BRESENHAM),
                        False)
            finish = time()
            self.time_ellipse.bresenham.append((finish - start) * 1_000)

            self.time_ellipse.radius.append(radius)


    def eventSetMethod(self, index: int):
        match index:
            case 0:
                self.method = Methods.METHOD_LIB
            case 1:
                self.method = Methods.METHOD_CANONICAL
            case 2:
                self.method = Methods.METHOD_PARAM
            case 3:
                self.method = Methods.METHOD_AVERAGE
            case 4:
                self.method = Methods.METHOD_BRESENHAM



    def initDesign(self):
        self.pixMap.fill(QColor(self.colorBG))
        self.pushButtonColorBG.setStyleSheet(f"background-color: {self.colorBG}")
        self.pushButtonColorCircle.setStyleSheet(f"background-color: {self.colorPen}")


    @staticmethod
    def eventChooseColor():
        return QColorDialog.getColor().name()


    def eventChangeColorBG(self):
        self.pushButtonColorBG.clicked.connect(self.changeColorBG)


    def eventChangeColorCircle(self):
        self.pushButtonColorCircle.clicked.connect(self.changeColorCircle)


    def changeColorBG(self):
        self.colorBG = self.eventChooseColor()
        self.pixMap.fill(QColor(self.colorBG))
        self.canvas.setPixmap(self.pixMap)
        self.pushButtonColorBG.setStyleSheet(f"background-color: {self.colorBG}")
        self.paint()


    def changeColorCircle(self):
        self.colorPen = self.eventChooseColor()
        self.pushButtonColorCircle.setStyleSheet(f"background-color: {self.colorPen}")


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


    def eventAddSpectorCircle(self):
        self.addSpectorCircle()
        self.paint()


    def addSpectorCircle(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_start_r = self.lineEditCircleSpectorR.text()
        tmp_step_r = self.lineEditStep.text()
        tmp_cnt = self.lineEditCount.text()
        array_result_start = checkFloatNum(tmp_cx, tmp_cy, tmp_start_r)
        array_result_step = checkIntNum(tmp_step_r, tmp_cnt)
        if array_result_start[0] == OK and array_result_step[0] == OK:
            cx = array_result_start[1]
            cy = array_result_start[2]
            if array_result_start[3] > 0 and array_result_step[1] > 0 and array_result_step[2] > 0:
                radius = array_result_start[3]
                step = array_result_step[1]
                for i in range(array_result_step[2]):
                        ellipse = Ellipse(cx, cy, radius, radius, self.colorPen, self.method)
                        self.ellipses.append(ellipse)
                        radius += step
            else:
                self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")


    def eventAddSpectorEllipse(self):
        self.addSpectorEllipse()
        self.paint()


    def addSpectorEllipse(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_start_h = self.lineEditElipseSpectorH.text()
        tmp_start_w = self.lineEditElipseSpectorW.text()
        tmp_step_r = self.lineEditStep.text()
        tmp_cnt = self.lineEditCount.text()
        array_result_start = checkFloatNum(tmp_cx, tmp_cy, tmp_start_h, tmp_start_w, tmp_step_r)
        array_result_step = checkIntNum(tmp_cnt)
        if array_result_start[0] == OK and array_result_step[0] == OK:
            cx = array_result_start[1]
            cy = array_result_start[2]
            if array_result_start[3] > 0 and array_result_start[4] > 0 and array_result_start[5] > 0 and array_result_step[1] > 0:
                h = array_result_start[3]
                w = array_result_start[4]
                step = array_result_start[5]
                for i in range(array_result_step[1]):
                    self.ellipses.append(Ellipse(cx, cy, h, w, self.colorPen, self.method))
                    h += step
                    w += step
            else:
                self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")


    def eventCleanCanvas(self):
        self.ellipses.clear()
        self.initQPainter()
        self.colorBG = 'black'
        self.colorPen = 'white'
        self.initDesign()
        self.paint()


    def paint(self):
        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorPen))
        painter.setPen(pen)

        for ellipse in self.ellipses:
            mainPainter(painter, pen, ellipse)
        painter.end()
        self.canvas.repaint()


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
