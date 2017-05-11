greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
TEMPLATE = app

win32:DEFINES += _WINSOCKAPI_

SOURCES += main.cpp \
    loginwindow.cpp \
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
    dialogmessage.cpp \
    message.cpp \
    dialogchangepassword.cpp \
    systemwindowprofessor.cpp \
    dialogaddsection.cpp

HEADERS += \
    loginwindow.h \
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
    dialogmessage.h \
    message.h \
    dialogchangepassword.h \
    systemwindowprofessor.h \
    dialogaddsection.h

FORMS += \
    loginwindow.ui \
    systemwindowadminstrator.ui \
    dialogmessage.ui \
    dialogchangepassword.ui \
    systemwindowprofessor.ui \
    dialogaddsection.ui

