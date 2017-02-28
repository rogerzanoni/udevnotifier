#ifndef UDEVNOTIFIER_MONITOR_H
#define UDEVNOTIFIER_MONITOR_H

#include "device.h"
#include "udevnotifier_global.h"

#include <libudev.h>


namespace UdevNotifier {

class UDEVNOTIFIERSHARED_EXPORT Monitor: public Device
{
public:
    Monitor(udev_device *device = nullptr, TYPE typen = MONITOR);
    ~Monitor();
};

}

#endif // UDEVNOTIFIER_MONITOR_H
