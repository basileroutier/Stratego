QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include (../config.pri)

CONFIG += c++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    uiController.cpp \
    uiboard.cpp \
    uicell.cpp \
    uicellepiece.cpp

HEADERS += \
    uiboard.h \
    mainwindow.h \
    uiController.h \
    uiboard.h \
    uicell.h \
    uicellepiece.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../stratego_model/release/ -lstratego_model
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../stratego_model/debug/ -lstratego_model
else:unix: LIBS += -L$$OUT_PWD/../stratego_model/ -lstratego_model

INCLUDEPATH += $$PWD/../stratego_model
DEPENDPATH += $$PWD/../stratego_model

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stratego_model/release/libstratego_model.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stratego_model/debug/libstratego_model.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stratego_model/release/stratego_model.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stratego_model/debug/stratego_model.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../stratego_model/libstratego_model.a
