#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T12:25:11
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo-player
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    playerwidget.cpp \
    visualisewidget.cpp \
    volumewidget.cpp

HEADERS  += mainwindow.h \
    playerwidget.h \
    visualisewidget.h \
    volumewidget.h

# FFT real

INCLUDEPATH += 3rdparty
HEADERS  += 3rdparty/ffft/Array.h \
            3rdparty/ffft/Array.hpp \
            3rdparty/ffft/DynArray.h \
            3rdparty/ffft/DynArray.hpp \
            3rdparty/ffft/FFTRealFixLen.h \
            3rdparty/ffft/FFTRealFixLen.hpp \
            3rdparty/ffft/FFTRealFixLenParam.h \
            3rdparty/ffft/FFTRealPassDirect.h \
            3rdparty/ffft/FFTRealPassDirect.hpp \
            3rdparty/ffft/FFTRealPassInverse.h \
            3rdparty/ffft/FFTRealPassInverse.hpp \
            3rdparty/ffft/FFTRealSelect.h \
            3rdparty/ffft/FFTRealSelect.hpp \
            3rdparty/ffft/FFTRealUseTrigo.h \
            3rdparty/ffft/FFTRealUseTrigo.hpp \
            3rdparty/ffft/OscSinCos.h \
            3rdparty/ffft/OscSinCos.hpp \
            3rdparty/ffft/def.h
	    
# Wrapper used to export the required instantiation of the FFTRealFixLen template
HEADERS  += fftreal_wrapper.h
SOURCES  += fftreal_wrapper.cpp
