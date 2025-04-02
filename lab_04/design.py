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
        MainWindow.resize(1241, 744)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 30, 700, 600))
        self.label.setText("")
        self.label.setObjectName("label")
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setGeometry(QtCore.QRect(830, 150, 331, 41))
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
        self.labelMethod.setGeometry(QtCore.QRect(920, 120, 191, 31))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.labelMethod.setFont(font)
        self.labelMethod.setObjectName("labelMethod")
        self.labelColorBG = QtWidgets.QLabel(self.centralwidget)
        self.labelColorBG.setGeometry(QtCore.QRect(800, 10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.labelColorBG.setFont(font)
        self.labelColorBG.setObjectName("labelColorBG")
        self.pushButtonColorBG = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorBG.setGeometry(QtCore.QRect(760, 50, 211, 41))
        self.pushButtonColorBG.setText("")
        self.pushButtonColorBG.setObjectName("pushButtonColorBG")
        self.pushButtonColorCircle = QtWidgets.QPushButton(self.centralwidget)
        self.pushButtonColorCircle.setGeometry(QtCore.QRect(1000, 50, 211, 41))
        self.pushButtonColorCircle.setText("")
        self.pushButtonColorCircle.setObjectName("pushButtonColorCircle")
        self.labelColorCircle = QtWidgets.QLabel(self.centralwidget)
        self.labelColorCircle.setGeometry(QtCore.QRect(1020, 10, 171, 31))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.labelColorCircle.setFont(font)
        self.labelColorCircle.setObjectName("labelColorCircle")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1241, 33))
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


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
