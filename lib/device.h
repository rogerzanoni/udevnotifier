#ifndef UDEVNOTIFIER__DEVICE_H
#define UDEVNOTIFIER__DEVICE_H

#include "udevnotifier_global.h"

#include <QtCore/QMetaType>
#include <QtCore/QThread>


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

    enum TIPO{

        MONITOR,
        WEBCAM
    };



    Device(udev_device *device = nullptr);
    Device(const Device &other);
    ~Device();

    QString node() const;
    QString subsystem() const;
    QString type() const;
    TIPO   Typedevice();

private:
    DevicePrivate * const d;


};

}

Q_DECLARE_METATYPE(UdevNotifier::Device)

#endif  // UDEVNOTIFIER__DEVICE_H
