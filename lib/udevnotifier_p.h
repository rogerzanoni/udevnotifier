#ifndef UDEVNOTIFIER_P_H
#define UDEVNOTIFIER_P_H

#include <QtCore/QStringList>


struct udev;
struct udev_monitor;


namespace UdevNotifier {

class UdevNotifierPrivate
{
public:
    UdevNotifierPrivate()
        : fdUdev(-1)
        , exit(true)
        , udev(nullptr)
        , udevMonitor(nullptr)
    {}

    QStringList groups;

    int fdUdev;

    /** flag that indicates if the thread should be running or not */
    bool exit;

    struct udev *udev;
    struct udev_monitor *udevMonitor;
};

}

#endif // UDEVNOTIFIER_P_H
