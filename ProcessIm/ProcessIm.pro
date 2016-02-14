#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T15:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcessIm
TEMPLATE = app

QT       += concurrent
SOURCES += main.cpp\
        mainwindow.cpp \
    infowindows.cpp \
    imagewindows.cpp \
    qlabel_image.cpp \
    histogramme.cpp \
    qimagetomat.cpp \
    traitement.cpp \
    detectioncouleurs.cpp \
    parametragetraitement.cpp \
    resultats.cpp \
    detectionforme.cpp \
    choixcouleur.cpp \
    comptageobjet.cpp \
    retrouverobjet.cpp \
    couleurschoix.cpp

HEADERS  += mainwindow.h \
    infowindows.h \
    imagewindows.h \
    histogramme.h \
    qlabel_image.h \
    qimagetomat.h \
    traitement.h \
    detectioncouleurs.h \
    parametragetraitement.h \
    resultats.h \
    detectionforme.h \
    choixcouleur.h \
    comptageobjet.h \
    retrouverobjet.h \
    defineprocessim.h \
    couleurschoix.h

FORMS    += mainwindow.ui \
    infowindows.ui \
    imagewindows.ui \
    histogramme.ui \
    detectioncouleurs.ui \
    parametragetraitement.ui \
    resultats.ui \
    detectionforme.ui \
    choixcouleur.ui \
    comptageobjet.ui \
    retrouverobjet.ui \
    couleurschoix.ui


DISTFILES += \
    Image/im0002.bmp
    actions/document-save-3.ico
    actions/zoom-in-3.ico
    actions/zoom-out-3.ico

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../OpenCV3_0/build/x64/vc12/lib/ -lopencv_world300
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../OpenCV3_0/build/x64/vc12/lib/ -lopencv_world300d

INCLUDEPATH += $$PWD/../../../../OpenCV3_0/build/include
DEPENDPATH += $$PWD/../../../../OpenCV3_0/build/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../dllBaumer/Lib/x64/ -lbgapi2_genicam
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../dllBaumer/Lib/x64/ -lbgapi2_genicam

INCLUDEPATH += $$PWD/../../dllBaumer/Inc
DEPENDPATH += $$PWD/../../dllBaumer/Inc
