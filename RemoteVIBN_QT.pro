QT       += widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authhandler.cpp \
    dataloader.cpp \
    filejsonloader.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    restapijsonloader.cpp \
    treeitem.cpp \
    treemodel.cpp \
    workpackage.cpp

HEADERS += \
    authhandler.h \
    dataloader.h \
    filejsonloader.h \
    jsonloader.h\
    logindialog.h \
    mainwindow.h \
    restapijsonloader.h \
    treeitem.h \
    treemodel.h \
    workpackage.h \
    authdata.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

RESOURCES   = request.qrc
CONFIG += lrelease

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
