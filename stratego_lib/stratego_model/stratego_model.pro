TEMPLATE = lib
TARGET = stratego_model
CONFIG += staticlib
include (../config.pri)
SOURCES += \
    board.cpp \
    case.cpp \
    direction.cpp \
    piece.cpp \
    game.cpp \
    position.cpp

HEADERS += \
    case.h \
    illegalDirectionException.hpp \
    illegalPieceException.hpp \
    illegalPositionException.hpp \
    illegalStateException.hpp \
    illegalTeamException.hpp \
    strategoException.hpp \
    stratego_model.h \
    stratego_model_global.h \
    board.h \
    casetype.h \
    direction.h \
    observable.h \
    piece.h \
    position.h \
    state.h \
    teamcolor.h \
    valuepiece.h \
    observer.h \
    game.h


# Default rules for deployment .

unix {
    target.path = /usr/lib
}
! isEmpty (target.path) : INSTALLS += target
DISTFILES +=
