######################################################################
# Automatically generated by qmake (3.1) Thu Nov 21 23:14:11 2024
######################################################################

TEMPLATE = lib

# Define the name of the library (without extension)
TARGET = pyqvnc
# Ensure that the shared option is used
CONFIG += shared
INCLUDEPATH += .
QT += core widgets
LIBS += -L.  -lvncclient

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += QVncViewer.hpp
SOURCES += QVncViewer.cpp
