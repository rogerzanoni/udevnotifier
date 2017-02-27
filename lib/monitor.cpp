#include "monitor.h"
#include "device.h"
#include <QtCore/QDebug>

namespace UdevNotifier {

Monitor::Monitor(udev_device *device)
    :Device(device)
{
    qDebug() << "qyesto è un monitr";
}

Monitor::~Monitor()
{

}

}
