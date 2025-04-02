# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'design.ui'
#
# Created by: PyQt5 UI code generator 5.15.11
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1300, 800)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.canvas = QtWidgets.QLabel(self.centralwidget)
        self.canvas.setGeometry(QtCore.QRect(10, 30, 700, 600))
        self.canvas.setText("")
        self.canvas.setObjectName("canvas")
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setGeometry(QtCore.QRect(840, 120, 371, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.comboBox.setFont(font)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.labelMethod = QtWidgets.QLabel(self.centralwidget)
        self.labelMethod.setGeometry(QtCore.QRect(910, 90, 241, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelMethod.setFont(font)
        self.labelMethod.setObjectName("labelMethod")
        self.labelColorBG = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG.setGeometry(QtCore.QRect(830, 10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG.setFont(font)
        self.labelColorBG.setObjectName("labelColorBG")
        self.pushButtonColorBG = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorBG.setGeometry(QtCore.QRect(790, 50, 211, 41))
        self.pushButtonColorBG.setText("")
        self.pushButtonColorBG.setObjectName("pushButtonColorBG")
        self.pushButtonColorCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorCircle.setGeometry(QtCore.QRect(1030, 50, 211, 41))
        self.pushButtonColorCircle.setText("")
        self.pushButtonColorCircle.setObjectName("pushButtonColorCircle")
        self.labelColorCircle = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircle.setGeometry(QtCore.QRect(1050, 10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircle.setFont(font)
        self.labelColorCircle.setObjectName("labelColorCircle")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(780, 180, 471, 20))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(870, 200, 221, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(780, 280, 481, 20))
        self.label_4.setObjectName("label_4")
        self.labelColorBG_2 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_2.setGeometry(QtCore.QRect(770, 300, 259, 70))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_2.setFont(font)
        self.labelColorBG_2.setObjectName("labelColorBG_2")
        self.lineEditCircleR = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCircleR.setGeometry(QtCore.QRect(790, 390, 221, 21))
        self.lineEditCircleR.setObjectName("lineEditCircleR")
        self.pushButtonDrawCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawCircle.setGeometry(QtCore.QRect(778, 450, 241, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawCircle.setFont(font)
        self.pushButtonDrawCircle.setObjectName("pushButtonDrawCircle")
        self.labelColorCircleR = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR.setGeometry(QtCore.QRect(770, 390, 21, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR.setFont(font)
        self.labelColorCircleR.setObjectName("labelColorCircleR")
        self.labelColorBG_3 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_3.setGeometry(QtCore.QRect(1040, 310, 259, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_3.setFont(font)
        self.labelColorBG_3.setObjectName("labelColorBG_3")
        self.pushButtonDrawEllipse = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawEllipse.setGeometry(QtCore.QRect(1050, 450, 231, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawEllipse.setFont(font)
        self.pushButtonDrawEllipse.setObjectName("pushButtonDrawEllipse")
        self.lineEditElipseH = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseH.setGeometry(QtCore.QRect(1050, 370, 221, 21))
        self.lineEditElipseH.setObjectName("lineEditElipseH")
        self.lineEditElipseW = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseW.setGeometry(QtCore.QRect(1050, 410, 221, 21))
        self.lineEditElipseW.setObjectName("lineEditElipseW")
        self.labelColorCircleR_2 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_2.setGeometry(QtCore.QRect(1030, 390, 21, 67))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_2.setFont(font)
        self.labelColorCircleR_2.setObjectName("labelColorCircleR_2")
        self.labelColorCircleR_3 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_3.setGeometry(QtCore.QRect(1030, 360, 21, 43))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_3.setFont(font)
        self.labelColorCircleR_3.setObjectName("labelColorCircleR_3")
        self.lineEditCX = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCX.setGeometry(QtCore.QRect(790, 250, 211, 21))
        self.lineEditCX.setObjectName("lineEditCX")
        self.lineEditCY = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCY.setGeometry(QtCore.QRect(1050, 250, 221, 21))
        self.lineEditCY.setObjectName("lineEditCY")
        self.labelColorYC = QtWidgets.QLabel(self.centralwidget)
        self.labelColorYC.setGeometry(QtCore.QRect(1020, 250, 31, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorYC.setFont(font)
        self.labelColorYC.setObjectName("labelColorYC")
        self.labelXC = QtWidgets.QLabel(self.centralwidget)
        self.labelXC.setGeometry(QtCore.QRect(760, 240, 31, 39))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelXC.setFont(font)
        self.labelXC.setObjectName("labelXC")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(780, 520, 481, 20))
        self.label_5.setObjectName("label_5")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1300, 33))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.comboBox.setItemText(0, _translate("MainWindow", "Библиотечная функция"))
        self.comboBox.setItemText(1, _translate("MainWindow", "Каноническое уравнение"))
        self.comboBox.setItemText(2, _translate("MainWindow", "Параметрическое уравнение"))
        self.comboBox.setItemText(3, _translate("MainWindow", "Алгоритм средней точки"))
        self.comboBox.setItemText(4, _translate("MainWindow", "Алгоритм Брезенхема"))
        self.labelMethod.setText(_translate("MainWindow", "Метод отрисовки"))
        self.labelColorBG.setText(_translate("MainWindow", "Цвет фона"))
        self.labelColorCircle.setText(_translate("MainWindow", "Цвет фигуры"))
        self.label_2.setText(_translate("MainWindow", "______________________________________________________________________________________________"))
        self.label_3.setText(_translate("MainWindow", "Координаты центра"))
        self.label_4.setText(_translate("MainWindow", "________________________________________________________________________________________________"))
        self.labelColorBG_2.setText(_translate("MainWindow", "Построение окружности"))
        self.pushButtonDrawCircle.setText(_translate("MainWindow", "Нарисовать\n"
"окружность"))
        self.labelColorCircleR.setText(_translate("MainWindow", "R"))
        self.labelColorBG_3.setText(_translate("MainWindow", "Построение элипса"))
        self.pushButtonDrawEllipse.setText(_translate("MainWindow", "Нарисовать\n"
"еллипс"))
        self.labelColorCircleR_2.setText(_translate("MainWindow", "W"))
        self.labelColorCircleR_3.setText(_translate("MainWindow", "H"))
        self.labelColorYC.setText(_translate("MainWindow", "Yc"))
        self.labelXC.setText(_translate("MainWindow", "Xc"))
        self.label_5.setText(_translate("MainWindow", "________________________________________________________________________________________________"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
