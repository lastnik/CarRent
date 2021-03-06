QT += quick
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PATH=\\\"$$PWD\\\"
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/header
INCLUDEPATH += $$PWD/model/header
INCLUDEPATH += $$PWD/header/msg

VPATH += \
        $$PWD/source \
        $$PWD/model/source

HEADERS += \
    $$PWD/header/calendar.h \
    $$PWD/header/clientnet.h \
    $$PWD/header/login.h \
    $$PWD/header/msg/imsg.h \
    $$PWD/header/msg/loginmsg.h \
    $$PWD/header/receiver.h \
    $$PWD/header/transmiter.h \
    $$PWD/header/core.h \
    $$PWD/header/msg/registrationmsg.h \
    $$PWD/model/header/documentsmodel.h \
    $$PWD/header/msg/accessmsg.h \
    $$PWD/model/header/carmodel.h \
    $$PWD/header/msg/carinfomsg.h \
    $$PWD/header/msg/registrationcarmsg.h \
    $$PWD/header/msg/confirmrentalmsg.h \
    $$PWD/header/msg/rentalinfomsg.h \
    $$PWD/header/msg/rentallistinfomsg.h \
    $$PWD/header/msg/rentalrespondmsg.h \
    $$PWD/model/header/rentaladmodel.h \
    $$PWD/header/msg/chatinfomsg.h \
    $$PWD/header/msg/chatslistmsg.h \
    $$PWD/model/header/chatmodel.h \
    header/msg/newmsgchatmsg.h \
    model/header/chatlistmodel.h




SOURCES += \
        calendar.cpp \
        clientnet.cpp \
        core.cpp \
        documentsmodel.cpp \
        accessmsg.cpp \
        carmodel.cpp \
        model/source/chatlistmodel.cpp \
        model/source/chatmodel.cpp \
        rentaladmodel.cpp \
        registrationmsg.cpp \
        receiver.cpp \
        loginmsg.cpp \
        carinfomsg.cpp \
        registrationcarmsg.cpp \
        confirmrentalmsg.cpp \
        rentalinfomsg.cpp \
        rentallistinfomsg.cpp \
        rentalrespondmsg.cpp \
        chatinfomsg.cpp \
        chatslistmsg.cpp \
        source/newmsgchatmsg.cpp \
        transmiter.cpp \
        login.cpp \
        main.cpp





RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    pages/MyBusyIndicator.qml

