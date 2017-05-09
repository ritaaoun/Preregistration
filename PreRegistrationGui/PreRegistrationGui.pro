greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
TEMPLATE = app

win32:DEFINES += _WINSOCKAPI_

SOURCES += main.cpp \
    loginwindow.cpp \
    systemwindow.cpp \
    apiservice.cpp \
    course.cpp \
    timeslot.cpp \
    section.cpp \
    user.cpp \
    systemwindowadminstrator.cpp \
    courserequest.cpp \
    parser.cpp \
    ClientServerInterface.cpp \
    NetworkClient.cpp \
    ClientInterface.cpp \
    userinfo.cpp \
    dialogmessage.cpp

HEADERS += \
    loginwindow.h \
    systemwindow.h \
    apiservice.h \
    course.h \
    timeslot.h \
    section.h \
    user.h \
    systemwindowadminstrator.h \
    courserequest.h \
    parser.h \
    ClientServerInterface.hpp \
    NetworkClient.hpp \
    ClientInterface.hpp \
    userinfo.h \
    dialogmessage.h

FORMS += \
    loginwindow.ui \
    systemwindow.ui \
    systemwindowadminstrator.ui \
    dialogmessage.ui

