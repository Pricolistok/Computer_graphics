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
        MainWindow.resize(1616, 1084)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.canvas = QtWidgets.QLabel(self.centralwidget)
        self.canvas.setGeometry(QtCore.QRect(30, 30, 1000, 1000))
        self.canvas.setText("")
        self.canvas.setObjectName("canvas")
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setGeometry(QtCore.QRect(1140, 100, 371, 41))
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
        self.labelMethod.setGeometry(QtCore.QRect(1210, 70, 241, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelMethod.setFont(font)
        self.labelMethod.setObjectName("labelMethod")
        self.labelColorBG = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG.setGeometry(QtCore.QRect(1130, -10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG.setFont(font)
        self.labelColorBG.setObjectName("labelColorBG")
        self.pushButtonColorBG = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorBG.setGeometry(QtCore.QRect(1090, 30, 211, 41))
        self.pushButtonColorBG.setText("")
        self.pushButtonColorBG.setObjectName("pushButtonColorBG")
        self.pushButtonColorCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorCircle.setGeometry(QtCore.QRect(1330, 30, 211, 41))
        self.pushButtonColorCircle.setText("")
        self.pushButtonColorCircle.setObjectName("pushButtonColorCircle")
        self.labelColorCircle = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircle.setGeometry(QtCore.QRect(1350, -10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircle.setFont(font)
        self.labelColorCircle.setObjectName("labelColorCircle")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(1080, 160, 471, 20))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(1170, 180, 221, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(1080, 260, 481, 20))
        self.label_4.setObjectName("label_4")
        self.labelColorBG_2 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_2.setGeometry(QtCore.QRect(1080, 260, 259, 70))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_2.setFont(font)
        self.labelColorBG_2.setObjectName("labelColorBG_2")
        self.lineEditCircleR = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCircleR.setGeometry(QtCore.QRect(1080, 340, 231, 21))
        self.lineEditCircleR.setObjectName("lineEditCircleR")
        self.pushButtonDrawCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawCircle.setGeometry(QtCore.QRect(1080, 450, 241, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawCircle.setFont(font)
        self.pushButtonDrawCircle.setObjectName("pushButtonDrawCircle")
        self.labelColorCircleR = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR.setGeometry(QtCore.QRect(1080, 310, 151, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR.setFont(font)
        self.labelColorCircleR.setObjectName("labelColorCircleR")
        self.labelColorBG_3 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_3.setGeometry(QtCore.QRect(1340, 270, 259, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_3.setFont(font)
        self.labelColorBG_3.setObjectName("labelColorBG_3")
        self.pushButtonDrawEllipse = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawEllipse.setGeometry(QtCore.QRect(1340, 450, 231, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawEllipse.setFont(font)
        self.pushButtonDrawEllipse.setObjectName("pushButtonDrawEllipse")
        self.lineEditElipseH = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseH.setGeometry(QtCore.QRect(1340, 340, 221, 21))
        self.lineEditElipseH.setObjectName("lineEditElipseH")
        self.lineEditElipseW = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseW.setGeometry(QtCore.QRect(1340, 410, 221, 21))
        self.lineEditElipseW.setObjectName("lineEditElipseW")
        self.labelColorCircleR_2 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_2.setGeometry(QtCore.QRect(1340, 370, 221, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_2.setFont(font)
        self.labelColorCircleR_2.setObjectName("labelColorCircleR_2")
        self.labelColorCircleR_3 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_3.setGeometry(QtCore.QRect(1340, 300, 161, 43))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_3.setFont(font)
        self.labelColorCircleR_3.setObjectName("labelColorCircleR_3")
        self.lineEditCX = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCX.setGeometry(QtCore.QRect(1090, 230, 211, 21))
        self.lineEditCX.setObjectName("lineEditCX")
        self.lineEditCY = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCY.setGeometry(QtCore.QRect(1350, 230, 221, 21))
        self.lineEditCY.setObjectName("lineEditCY")
        self.labelColorYC = QtWidgets.QLabel(self.centralwidget)
        self.labelColorYC.setGeometry(QtCore.QRect(1320, 230, 31, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorYC.setFont(font)
        self.labelColorYC.setObjectName("labelColorYC")
        self.labelXC = QtWidgets.QLabel(self.centralwidget)
        self.labelXC.setGeometry(QtCore.QRect(1060, 220, 31, 39))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelXC.setFont(font)
        self.labelXC.setObjectName("labelXC")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(1080, 520, 511, 20))
        self.label_5.setObjectName("label_5")
        self.pushButtonDrawSpectorEllipse = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawSpectorEllipse.setGeometry(QtCore.QRect(1350, 850, 231, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawSpectorEllipse.setFont(font)
        self.pushButtonDrawSpectorEllipse.setObjectName("pushButtonDrawSpectorEllipse")
        self.labelColorBG_4 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_4.setGeometry(QtCore.QRect(1350, 540, 259, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_4.setFont(font)
        self.labelColorBG_4.setObjectName("labelColorBG_4")
        self.labelColorCircleR_4 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_4.setGeometry(QtCore.QRect(1340, 640, 51, 43))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_4.setFont(font)
        self.labelColorCircleR_4.setText("")
        self.labelColorCircleR_4.setObjectName("labelColorCircleR_4")
        self.lineEditElipseSpectorH = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseSpectorH.setGeometry(QtCore.QRect(1350, 710, 221, 21))
        self.lineEditElipseSpectorH.setObjectName("lineEditElipseSpectorH")
        self.pushButtonDrawSpectorCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonDrawSpectorCircle.setGeometry(QtCore.QRect(1080, 850, 241, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonDrawSpectorCircle.setFont(font)
        self.pushButtonDrawSpectorCircle.setObjectName("pushButtonDrawSpectorCircle")
        self.labelColorBG_5 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_5.setGeometry(QtCore.QRect(1080, 540, 241, 51))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_5.setFont(font)
        self.labelColorBG_5.setObjectName("labelColorBG_5")
        self.lineEditCircleSpectorR = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCircleSpectorR.setGeometry(QtCore.QRect(1080, 640, 221, 21))
        self.lineEditCircleSpectorR.setObjectName("lineEditCircleSpectorR")
        self.labelColorCircleR_5 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_5.setGeometry(QtCore.QRect(1080, 610, 201, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_5.setFont(font)
        self.labelColorCircleR_5.setObjectName("labelColorCircleR_5")
        self.lineEditElipseSpectorW = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditElipseSpectorW.setGeometry(QtCore.QRect(1350, 640, 221, 21))
        self.lineEditElipseSpectorW.setObjectName("lineEditElipseSpectorW")
        self.labelColorCircleR_6 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_6.setGeometry(QtCore.QRect(1350, 670, 211, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_6.setFont(font)
        self.labelColorCircleR_6.setObjectName("labelColorCircleR_6")
        self.labelColorBG_6 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG_6.setGeometry(QtCore.QRect(1350, 600, 259, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorBG_6.setFont(font)
        self.labelColorBG_6.setObjectName("labelColorBG_6")
        self.labelColorCircleR_7 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_7.setGeometry(QtCore.QRect(1240, 730, 201, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_7.setFont(font)
        self.labelColorCircleR_7.setObjectName("labelColorCircleR_7")
        self.lineEditStep = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditStep.setGeometry(QtCore.QRect(1240, 760, 221, 21))
        self.lineEditStep.setObjectName("lineEditStep")
        self.lineEditCount = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEditCount.setGeometry(QtCore.QRect(1240, 820, 221, 21))
        self.lineEditCount.setObjectName("lineEditCount")
        self.labelColorCircleR_8 = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircleR_8.setGeometry(QtCore.QRect(1240, 790, 251, 21))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelColorCircleR_8.setFont(font)
        self.labelColorCircleR_8.setObjectName("labelColorCircleR_8")
        self.pushButtonClear = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonClear.setGeometry(QtCore.QRect(1240, 920, 231, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonClear.setFont(font)
        self.pushButtonClear.setObjectName("pushButtonClear")
        self.pushButtonData = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonData.setGeometry(QtCore.QRect(1240, 990, 231, 61))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.pushButtonData.setFont(font)
        self.pushButtonData.setObjectName("pushButtonData")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1616, 33))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "CG lab_04"))
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
        self.labelColorCircleR.setText(_translate("MainWindow", "Радиус"))
        self.labelColorBG_3.setText(_translate("MainWindow", "Построение эллипса"))
        self.pushButtonDrawEllipse.setText(_translate("MainWindow", "Нарисовать\n"
"эллипс"))
        self.labelColorCircleR_2.setText(_translate("MainWindow", "Ширина"))
        self.labelColorCircleR_3.setText(_translate("MainWindow", "Длина"))
        self.labelColorYC.setText(_translate("MainWindow", "Yc"))
        self.labelXC.setText(_translate("MainWindow", "Xc"))
        self.label_5.setText(_translate("MainWindow", "__________________________________________________________________________________________________"))
        self.pushButtonDrawSpectorEllipse.setText(_translate("MainWindow", "Нарисовать спектор\n"
"эллипса"))
        self.labelColorBG_4.setText(_translate("MainWindow", "Построение спектра\n"
"эллипса"))
        self.pushButtonDrawSpectorCircle.setText(_translate("MainWindow", "Нарисовать спектор\n"
"окружности"))
        self.labelColorBG_5.setText(_translate("MainWindow", "Построение спектра\n"
"окружности"))
        self.labelColorCircleR_5.setText(_translate("MainWindow", "Начальный радиус"))
        self.labelColorCircleR_6.setText(_translate("MainWindow", "Начальная высота"))
        self.labelColorBG_6.setText(_translate("MainWindow", "Начальная длина"))
        self.labelColorCircleR_7.setText(_translate("MainWindow", "Шаг отрисовки"))
        self.labelColorCircleR_8.setText(_translate("MainWindow", "Количество фигур"))
        self.pushButtonClear.setText(_translate("MainWindow", "Очистка"))
        self.pushButtonData.setText(_translate("MainWindow", "Справка"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
