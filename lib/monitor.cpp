#include "monitor.h"
#include "device.h"
#include "device_p.h"
#include <QtCore/QDebug>

namespace UdevNotifier {


/*Monitor::Monitor(udev_device* device)
    : w(new DevicePrivate())

{
    w->device = device;

     if(w->type=="drm_minor"){

          qDebug() << "Questò è un monitor" ;
     }else
 qDebug() << "Questò NON é monitor" ;

}
*/

Monitor::Monitor(udev_device* device):Device(device)
{
          qDebug() << "Questò è un monitor" ;


}

}
