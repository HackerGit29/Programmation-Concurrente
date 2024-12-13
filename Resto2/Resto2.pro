TEMPLATE = app
TARGET = Resto2

QT       += \
            core gui  \
            core gui sql \
             network \



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += console


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alertes.cpp \
    client.cpp \
    clientcontroller.cpp \
    controldialog.cpp \
    employee.cpp \
    employeecontroller.cpp \
    equipement.cpp \
    fridge.cpp \
    fridgecontroller.cpp \
    gameSettings.cpp \
    ingredient.cpp \
    ingredientfactory.cpp \
    lave.cpp \
    lavecontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menucontroller.cpp \
    order.cpp \
    plongeur.cpp \
    plongeurcontroller.cpp \
    staff.cpp \
    stockwindow.cpp \
    table.cpp \
    tablecontroller.cpp \
    tests/test_client.cpp


HEADERS += \
    GraphicsPixmapItemWithProperties.h \
    alertes.h \
    client.h \
    clientcontroller.h \
    controldialog.h \
    employee.h \
    employeecontroller.h \
    fridge.h \
    fridgecontroller.h \
    gameSettings.h \
    ingredient.h \
    ingredientfactory.h \
    lave.h \
    lavecontroller.h \
    mainwindow.h \
    menu.h \
    menucontroller.h \
    order.h \
    plongeur.h \
    plongeurcontroller.h \
    staff.h \
    stockwindow.h \
    table.h \
    tablecontroller.h




FORMS += \
    controldialog.ui \
    gameSettings.ui \
    mainwindow.ui \
    stockwindow.ui



RESOURCES += ressources.qrc



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    tests/test_client.pro

