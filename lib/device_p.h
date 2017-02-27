#ifndef UDEVNOTIFIER_DEVICE_P_H
#define UDEVNOTIFIER_DEVICE_P_H

#include <QtCore/QString>

#include <libudev.h>



namespace UdevNotifier {

/**
 * @class DevicePrivate
 * @brief The Device's private class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */
class DevicePrivate
{
public:
    DevicePrivate()
        : device(nullptr)
    {}
    ~DevicePrivate()
    {
        // destroy the relevant device
        udev_device_unref(device);
    }

    QString node;
    QString subsystem;
    QString type;

    udev_device *device;
};

}

#endif  // UDEVNOTIFIER_DEVICE_P_H
