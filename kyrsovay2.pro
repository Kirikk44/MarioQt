QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorwin.cpp \
    block.cpp \
    characters.cpp \
    flag.cpp \
    helpwin.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mobs.cpp

HEADERS += \
    authorwin.h \
    block.h \
    characters.h \
    flag.h \
    helpwin.h \
    mainwindow.h \
    map.h \
    mobs.h

FORMS += \
    authorwin.ui \
    helpwin.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sprites.qrc
