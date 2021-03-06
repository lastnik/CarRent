QT += quick
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PATH=\\\"$$PWD\\\"
DEFINES += SERVERPATH=\\\"$$PWD/../\\\"
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=  $$PWD/../CarRent/header/msg
INCLUDEPATH +=  $$PWD/header

VPATH += \
        $$PWD/source \
        $$PWD/model/source

HEADERS += \
    $$PWD/header/clientnet.h \
    $$PWD/header/login.h \
    $$PWD/header/receiver.h \
    $$PWD/header/transmiter.h \
    $$PWD/header/core.h \
    $$PWD/../CarRent/header/msg/loginmsg.h \
    $$PWD/../CarRent/header/msg/accessmsg.h \
    $$PWD/../CarRent/header/msg/registrationmsg.h \
    $$PWD/../CarRent/header/msg/registrationcarmsg.h \
    $$PWD/../CarRent/header/msg/imsg.h


SOURCES += \
        clientnet.cpp \
        core.cpp \
        receiver.cpp \
        transmiter.cpp \
        login.cpp \
        main.cpp \
        $$PWD/../CarRent/source/loginmsg.cpp \
        $$PWD/../CarRent/source/accessmsg.cpp \
        $$PWD/../CarRent/source/registrationmsg.cpp \
        $$PWD/../CarRent/source/registrationcarmsg.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

