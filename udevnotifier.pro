TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    lib \
    example

OTHER_FILES += include/UdevNotifier

example.subdir = $$PWD/example
udevnotifier.subdir = $$PWD/lib

unix {
  isEmpty(PREFIX): PREFIX = /usr
  headers.files = include/UdevNotifier/Device \
                  include/UdevNotifier/Monitor \
                  include/UdevNotifier/UdevNotifier \
                  include/UdevNotifier/Webcam \
                  lib/device.h \
                  lib/monitor.h \
                  lib/udevnotifier.h \
                  lib/udevnotifier_global.h \
                  lib/webcam.h

  headers.path = $${PREFIX}/include/UdevNotifier
  INSTALLS += headers
}
