import sys
from PyQt5.QtGui import QPen, QColor, QPainter, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QColorDialog, QMessageBox
from design import Ui_MainWindow
from consts import *
from errors import *
from ellipses import Ellipse


def checkNum(*args):
    error_code = OK
    array_result = [error_code]
    try:
        for i in args:
            array_result.append(float(i))
    except ValueError:
        array_result[-1] = 0
        array_result[0] = ERROR_INPUT_DATA
    return array_result


class MainApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.painter = None
        self.pixMap = None
        self.pen = None

        self.colorBG = 'black'
        self.colorPen = 'white'

        self.ellipses = []

        self.initConnections()
        self.initQPainter()
        self.initDesign()


    def initQPainter(self):
        self.pixMap = QPixmap(WIDTH_CANVAS, HEIGHT_CANVAS)
        self.canvas.setPixmap(self.pixMap)
        self.painter = QPainter(self.canvas.pixmap())
        self.pen = QPen()
        self.pen.setColor(QColor(self.colorPen))
        self.painter.setPen(self.pen)
        self.painter.end()


    def initConnections(self):
        self.pushButtonColorBG.clicked.connect(self.changeColorBG)
        self.pushButtonColorCircle.clicked.connect(self.changeColorCircle)
        self.pushButtonDrawCircle.clicked.connect(self.addCircle)
        self.pushButtonDrawEllipse.clicked.connect(self.addEllipse)


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
        self.pen.setColor(QColor(self.colorPen))


    @staticmethod
    def senderErrorMessage(text):
        message = QMessageBox()
        message.setWindowTitle("Ошибка")
        message.setText(text)
        message.exec_()


    def addCircle(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_r = self.lineEditCircleR.text()
        array_result = checkNum(tmp_cx, tmp_cy, tmp_r)
        if array_result[0] == OK:
            if array_result[2] > 0:
                ellipse = Ellipse(array_result[0], array_result[1], array_result[2], array_result[2], self.colorPen)
                self.ellipses.append(ellipse)
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения круга!")


    def addEllipse(self):
        tmp_cx = self.lineEditCX.text()
        tmp_cy = self.lineEditCY.text()
        tmp_rx = self.lineEditElipseW.text()
        tmp_ry = self.lineEditElipseH.text()
        array_result = checkNum(tmp_cx, tmp_cy, tmp_rx, tmp_ry)
        if array_result[0] == OK:
            if array_result[2] > 0:
                ellipse = Ellipse(array_result[0], array_result[1], array_result[2], array_result[3], self.colorPen)
                self.ellipses.append(ellipse)
        else:
            self.senderErrorMessage("Ошибка при вводе значений построения эллипса!")


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()