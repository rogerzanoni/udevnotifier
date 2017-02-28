#ifndef WEBCAM_H
#define WEBCAM_H

#include <libudev.h>
#include <QtCore/QString>
#include "device.h"

class udev_device;

namespace UdevNotifier{

class UDEVNOTIFIERSHARED_EXPORT Webcam: public Device
{
public:
    Webcam(udev_device *device = nullptr, TYPE typeD = WEBCAM);
    ~Webcam();
};

}
#endif // WEBCAM_H
