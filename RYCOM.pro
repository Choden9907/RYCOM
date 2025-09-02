#-------------------------------------------------
#
# Project created by QtCreator 2021-01-27T18:59:42
#
#-------------------------------------------------

#添加串口支持
QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RYCOM
TEMPLATE = app
INCLUDEPATH += $$PWD/src  # 关键配置
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#for win
RC_ICONS = src\resource\ico\rymculogo.ico
# for mac
ICON = src\resource\ico\rymculogo.icns
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
UI_DIR=.\src

SOURCES += \
    src/frameparse.cpp \
    src\main.cpp \
    src\mainwindow.cpp \
    src\mycombobox.cpp \
    src\ryisp.cpp \
    src\mycom.cpp \
    src\HexToBin.cpp \
    src\ry_ymodem.cpp \
    src\myfilewatcher.cpp \
    src\ryesp32isp.cpp

HEADERS += \
    src/frameparse.h \
    src\mainwindow.h \
    src\mycombobox.h \
    src\ryisp.h \
    src\mycom.h \
    src\HexToBin.h \
    src\HexToBin.h \
    src\ry_ymodem.h \
    src\myfilewatcher.h \
    src\ryesp32isp.h \
    src\include\esp32\esp32_protocol.h

FORMS += \
    src\forms\mainwindow.ui

RESOURCES += \
    src\resource\rycomres.qrc

DISTFILES += \
    Ggg.qml \
    GggForm.ui.qml
