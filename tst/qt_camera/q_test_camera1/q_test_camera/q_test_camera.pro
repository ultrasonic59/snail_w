# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = q_test_camera
DESTDIR = ../Win32/Debug
QT += core multimedia network opengl widgets gui printsupport multimediawidgets
CONFIG += debug
DEFINES += WIN64 QT_WIDGETS_LIB QT_MULTIMEDIA_LIB QT_MULTIMEDIAWIDGETS_LIB QT_NETWORK_LIB
INCLUDEPATH += . \
    ./GeneratedFiles \
    ./GeneratedFiles/Debug
LIBS += -L"$(QTDIR)/plugins/imageformats" \
    -L"$(QTDIR)/plugins/platforms" \
    -L"$(QTDIR)/plugins/mediaservice" \
    -lqicod \
    -lqwindowsd \
    -ldsengined \
    -lopengl32 \
    -lws2_32 \
    -limm32 \
    -lwinmm \
    -lSetupapi \
    -lglu32
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./mainwindow.h
SOURCES += ./main.cpp \
    ./mainwindow.cpp
FORMS += ./mainwindow.ui
RESOURCES += q_test_camera.qrc
