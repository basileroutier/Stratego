TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
include (../config.pri)

SOURCES += \
        main.cpp \
        controller.cpp \
        view.cpp

HEADERS += \
        controller.h \
        view.h

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
