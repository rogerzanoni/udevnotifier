#include "device.h"
#include "device_p.h"

namespace UdevNotifier {

Device::Device()
    : d(new DevicePrivate)
{
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
