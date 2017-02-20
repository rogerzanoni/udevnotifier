#ifndef UDEVNOTIFIER__DEVICE_H
#define UDEVNOTIFIER__DEVICE_H

#include "udevnotifier_global.h"


namespace UdevNotifier {

class DevicePrivate;

class UDEVNOTIFIERSHARED_EXPORT Device
{
public:
    Device();
    ~Device();

    QString node() const;
    QString subsystem() const;
    QString type() const;

private:
    DevicePrivate * const d;
};

}

#endif  // UDEVNOTIFIER__DEVICE_H
