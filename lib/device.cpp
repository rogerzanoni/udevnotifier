#include "device.h"
#include "device_p.h"
#include <libudev.h>
#include <QtCore/QDebug>

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


      //  qDebug() << QString("%1 - %2 - %3").arg(d->node).arg(d->subsystem).arg(d->type);
        qDebug()<< typeDevice();
        qDebug() << "node " << d->node;
        qDebug() << "subsystem:" << d->subsystem;
        qDebug() << "type: " << d->type;

        qDebug() << "DEVPATH: " << udev_device_get_devpath(d->device);
        qDebug() << "SYSPATH: " << udev_device_get_syspath(d->device);
        qDebug() << "SYSNAME: " << udev_device_get_sysname(d->device);
        qDebug() << "IS INIT: " << udev_device_get_is_initialized(d->device);
        qDebug() << "PRODUCT: " << udev_device_get_sysattr_value(d->device, "product");


        qDebug()<<"**************************************************************";

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

Device::TYPE Device::typeDevice(){

 if(d->type=="drm_minor") {
    return MONITOR;
    }

 if(d->subsystem=="video4linux") {
    return WEBCAM;
    }
 return DEVICEUSB;
}

}
