#ifndef UDEVNOTIFIER__DEVICE_H
#define UDEVNOTIFIER__DEVICE_H

#include "udevnotifier_global.h"
#include <QtCore/QMetaType>

class udev_device;

namespace UdevNotifier {

class DevicePrivate;


/**
 * @class Device
 * @brief The UdevNotifier Device class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * This class describes a device on the system detected by the UdevNotifier
 */
class UDEVNOTIFIERSHARED_EXPORT Device
{
public:

    enum DataType {
        MONITOR,
        WEBCAM,
        USBDEVICE
    };

    Device(udev_device *device = nullptr, DataType deviceType = USBDEVICE);
    Device(const Device &other);
    ~Device();

    QString node() const;
    QString subsystem() const;
    QString type() const;
    DataType deviceType() const;

private:
    DevicePrivate * const d;
    DataType m_deviceType;
};

}

Q_DECLARE_METATYPE(UdevNotifier::Device)

#endif  // UDEVNOTIFIER__DEVICE_H
