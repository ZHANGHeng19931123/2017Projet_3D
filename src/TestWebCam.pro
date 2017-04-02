#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T11:26:13
#
#-------------------------------------------------

QT       -= gui

TARGET = TestWebCam
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_webcam.cpp \
    detector.cpp \
    toolimage.cpp

INCLUDEPATH +=$$(OPENCV_DIR)\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect

HEADERS += \
    detector.h \
    toolimage.h


