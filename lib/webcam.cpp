#include "webcam.h"

namespace UdevNotifier {

Webcam::Webcam(udev_device *device)
    : Device(device, WEBCAM)
{
}
Webcam::~Webcam()
{
}

}
