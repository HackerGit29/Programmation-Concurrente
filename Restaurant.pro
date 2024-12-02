QT       += core gui
QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += console


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chaise.cpp \
    chaisecontroller.cpp \
    client.cpp \
    clientcontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    ordercontroller.cpp \
    table.cpp \
    tablecontroller.cpp

HEADERS += \
    chaise.h \
    chaisecontroller.h \
    client.h \
    clientcontroller.h \
    mainwindow.h \
    order.h \
    ordercontroller.h \
    table.h \
    tablecontroller.h

FORMS += \
    mainwindow.ui


RESOURCES += ressources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
