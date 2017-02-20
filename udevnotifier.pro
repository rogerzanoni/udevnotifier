TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    udevnotifier \
    example


OTHER_FILES += \
    include/Device \
    include/UdevNotifier

example.subdir = $$PWD/example
udevnotifier.subdir = $$PWD/lib
