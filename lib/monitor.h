#ifndef MONITOR_H
#define MONITOR_H
#include "device.h"
#include <libudev.h>

class udev_device;

namespace UdevNotifier {

class Monitor: public Device
{
public:
    Monitor(udev_device *device = nullptr);

private:
};
}
#endif // MONITOR_H
