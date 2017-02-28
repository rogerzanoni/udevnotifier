#include "webcam.h"
#include "device.h"
#include "device_p.h"
#include <QtCore/QDebug>
namespace UdevNotifier {

Webcam::Webcam(udev_device *device,TYPE typeD):Device(device,typeD)
{
    qDebug() <<"Questa p una webcam";
}
Webcam::~Webcam()
{
}

}
