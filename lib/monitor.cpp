#include "monitor.h"
#include "device.h"


namespace UdevNotifier {

Monitor::Monitor(udev_device *device)
    :Device(device)
{
}
<<<<<<< HEAD
*/

Monitor::Monitor(udev_device* device):Device(device)
{
          qDebug() << "Questò è un monitor" ;


=======

Monitor::~Monitor()
{
>>>>>>> f16a570cd29cfaab5c6a57cff107e550d9dc65ee
}

}
