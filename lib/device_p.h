#ifndef UDEVNOTIFIER_DEVICE_P_H
#define UDEVNOTIFIER_DEVICE_P_H

#include <QtCore/QString>


class udev_device;



namespace UdevNotifier {

class DevicePrivate
{
public:
    DevicePrivate() {}
    ~DevicePrivate() {}

    QString node;
    QString subsystem;
    QString type;

    udev_device *device;
};

}

#endif  // UDEVNOTIFIER_DEVICE_P_H
