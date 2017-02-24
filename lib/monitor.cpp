#include "monitor.h"
#include "device.h"
#include "device_p.h"
#include <QtCore/QDebug>

namespace UdevNotifier {
Monitor::Monitor(udev_device* device):Device(device)
{
        qDebug() << "Questò è un monitor" << subsystem();
}
}
