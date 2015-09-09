#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T11:07:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessS3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboardwidget.cpp \
    game.cpp \
    piece.cpp \
    player.cpp \
    position.cpp \
    board.cpp \
    move.cpp

HEADERS  += mainwindow.h \
    chessboardwidget.h \
    enums.h \
    game.h \
    piece.h \
    player.h \
    position.h \
    board.h \
    move.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Images.qrc
