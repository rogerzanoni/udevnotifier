#include "webcam.h"
#include "device.h"
#include "device_p.h"
#include <QtCore/QDebug>

namespace UdevNotifier {

Webcam::Webcam(udev_device *device)
    :Device(device, WEBCAM)
{
}
Webcam::~Webcam()
{
}

}
