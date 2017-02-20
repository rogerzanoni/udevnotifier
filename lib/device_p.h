#ifndef UDEVNOTIFIER_DEVICE_P_H
#define UDEVNOTIFIER_DEVICE_P_H

#include <QtCore/QString>


namespace UdevNotifier {

class DevicePrivate
{
public:
    DevicePrivate() {}
    ~DevicePrivate() {}

    QString node;
    QString subsystem;
    QString type;
};

}

#endif  // UDEVNOTIFIER_DEVICE_P_H
