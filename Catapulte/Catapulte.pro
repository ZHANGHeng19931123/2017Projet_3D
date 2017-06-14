#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T17:52:17
#
#-------------------------------------------------

QT += core gui opengl

LIBS += -IGL \
    -L \
    -lglu32 \
    -lGLU \
    -lm \
    -lglut \
    -lGL \
    -L$$(OPENCV_DIR)\lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Catapulte
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trebuchet.cpp \
    myglwidget.cpp \
    ToolOpenGL.cpp \
    floor.cpp \
    detector.cpp \
    toolimage.cpp \
    match.cpp \
    throw.cpp

HEADERS  += mainwindow.h \
    trebuchet.h \
    myglwidget.h \
    ToolOpenGL.h \
    floor.h \
    detector.h \
    toolimage.h \
    match.h \
    throw.h

FORMS    += mainwindow.ui
