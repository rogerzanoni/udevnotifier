#include "monitor.h"
#include "device.h"

namespace UdevNotifier {

Monitor::Monitor(udev_device *device, TYPE n)
    :Device(device,n)
{

}

Monitor::~Monitor()
{
}

}
