QT += core

TARGET = udevnotifier
TEMPLATE = lib

DEFINES += UDEVNOTIFIER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    device.cpp \
<<<<<<< HEAD
    udevnotifier.cpp \
    monitor.cpp  \
    webcam.cpp
=======
    monitor.cpp \
    udevnotifier.cpp

>>>>>>> f16a570cd29cfaab5c6a57cff107e550d9dc65ee

HEADERS += \
    device.h \
    device_p.h \
    monitor.h  \
    udevnotifier.h \
    udevnotifier_global.h \
<<<<<<< HEAD
    udevnotifier_p.h \
    monitor.h \
   webcam.h
=======
    udevnotifier_p.h

>>>>>>> f16a570cd29cfaab5c6a57cff107e550d9dc65ee


LIBS += -ludev

unix {
    target.path = /usr/lib
    INSTALLS += target
}
