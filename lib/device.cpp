#include "device.h"
#include "device_p.h"

#include <libudev.h>

namespace UdevNotifier {


Device::Device(udev_device* device)
    : d(new DevicePrivate)
{
    d->device = device;

    // populate basic info
    if (d->device) {
        d->node = udev_device_get_devnode(d->device);
        d->subsystem = udev_device_get_subsystem(d->device);
        d->type = udev_device_get_devtype(d->device);
    }
}

Device::Device(const UdevNotifier::Device &other)
    : d(new DevicePrivate)
{
    d->device = other.d->device;
    d->node = other.node();
    d->subsystem = other.subsystem();
    d->type = other.type();
}


Device::~Device()
{
    delete d;
}

QString Device::node() const
{
    return d->node;
}

QString Device::subsystem() const
{
    return d->subsystem;
}

QString Device::type() const
{
    return d->type;
}

}
