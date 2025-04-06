import sys
from PyQt5.QtCore import QRectF
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox
from design import Ui_MainWindow
from consts import *
from errors import *
from ellipses import Ellipse


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
        self.method = METHOD_LIB

        self.ellipses = []

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
        self.comboBox.activated.connect(self.eventSetMethod)


    def eventSetMethod(self, index: int):
        match index:
            case 0:
                self.method = METHOD_LIB
            case 1:
                self.method = METHOD_CANONICAL
            case 2:
                self.method = METHOD_CANONICAL
            case 3:
                self.method = METHOD_CANONICAL
            case 4:
                self.method = METHOD_LIB



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


    def addEllipse(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_rx = self.lineEditElipseW.text()
        tmp_ry = self.lineEditElipseH.text()
        array_result = checkFloatNum(tmp_cx, tmp_cy, tmp_rx, tmp_ry)
        if array_result[0] == OK:
            if array_result[2] > 0:
                ellipse = Ellipse(array_result[1], array_result[2], array_result[3] / 2, array_result[4] / 2, self.colorPen, self.method)
                self.ellipses.append(ellipse)
            else:
                self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")


    def eventAddSpectorCircle(self):
        self.addSpectorCircle()


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


    def addSpectorEllipse(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_start_h = self.lineEditCircleSpectorH.text()
        tmp_start_w = self.lineEditCircleSpectorW.text()
        tmp_step_r = self.lineEditStep.text()
        tmp_cnt = self.lineEditCount.text()
        array_result_start = checkFloatNum(tmp_cx, tmp_cy, tmp_start_h, tmp_start_w)
        array_result_step = checkIntNum(tmp_step_r, tmp_cnt)
        if array_result_start[0] == OK and array_result_step[0] == OK:
            cx = array_result_start[1]
            cy = array_result_start[2]
            if array_result_start[3] > 0 and array_result_step[1] > 0 and array_result_step[2] > 0:
                h = array_result_start[3]
                w = array_result_start[4]
                step = array_result_step[1]
                for i in range(array_result_step[2]):
                        ellipse = Ellipse(cx, cy, h / 2, w / 2, self.colorPen, self.method)
                        self.ellipses.append(ellipse)
                        h += step
                        w += step
            else:
                self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")
        else:
            self.senderErrorMessage("Ошибка при вводе значений спектра кругов!")


    def eventCleanCanvas(self):
        self.ellipses.clear()
        self.paint()


    def paint(self):
        painter = QPainter(self.canvas.pixmap())
        pen = QPen()
        pen.setColor(QColor(self.colorPen))
        painter.setPen(pen)

        for ellipse in self.ellipses:
            print(ellipse.color)
            pen.setColor(QColor(ellipse.color))
            painter.setPen(pen)
            rect = QRectF(
                (ellipse.cx - ellipse.rx) + X_OFFSET,
                Y_OFFSET - (ellipse.cy + ellipse.ry),
                ellipse.rx * 2,
                ellipse.ry * 2
            )
            print((ellipse.cx - ellipse.rx) + X_OFFSET)
            print(Y_OFFSET - (ellipse.cy - ellipse.ry))
            painter.drawEllipse(rect)
        painter.end()
        self.canvas.repaint()


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
