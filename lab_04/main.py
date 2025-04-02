import sys
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPen, QPainter, QColor, QPixmap
from design import Ui_MainWindow


class MainApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.colorBG = 'black'
        self.colorCircle = 'white'
        self.eventChangeColorBG()
        self.eventChangeColorCircle()


    @staticmethod
    def eventChooseColor():
        return QtWidgets.QColorDialog.getColor().name()


    def eventChangeColorBG(self):
        self.pushButtonColorBG.clicked.connect(self.changeColorBG)


    def eventChangeColorCircle(self):
        self.pushButtonColorCircle.clicked.connect(self.changeColorCircle)


    def changeColorBG(self):
        self.colorBG = self.eventChooseColor()
        self.pushButtonColorBG.setStyleSheet(f"background-color: {self.colorBG}")


    def changeColorCircle(self):
        self.colorCircle = self.eventChooseColor()
        self.pushButtonColorCircle.setStyleSheet(f"background-color: {self.colorCircle}")



def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()