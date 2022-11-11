QT       += core gui opengl widgets openglwidgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asteroid.cpp \
    gamerender.cpp \
    main.cpp \
    mainwindow.cpp \
    ship.cpp \
    startwindow.cpp \
    station.cpp \
    universe.cpp \
    utils.cpp \
    webcam.cpp

HEADERS += \
    asteroid.h \
    gamerender.h \
    mainwindow.h \
    ship.h \
    startwindow.h \
    station.h \
    universe.h \
    utils.h \
    webcam.h

#Debut Open CV
INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core455 \
    -lopencv_highgui455 \
    -lopencv_imgproc455 \
    -lopencv_imgcodecs455 \
    -lopencv_videoio455 \
    -lopencv_features2d455 \
    -lopencv_objdetect455 \
    -lopencv_calib3d455

#Fin Open CV

#Debut Open GL
# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}


#TEMPLATE  = app

#FIn Open GL



FORMS += \
    mainwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    closed_frontal_palm.xml \
    fist.xml


RESOURCES += \
    res.qrc

