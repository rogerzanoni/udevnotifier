#include "device.h"
#include "udevnotifier.h"
#include "udevnotifier_p.h"


#include <libudev.h>
#include <poll.h>


#include <QtCore/QDebug>


namespace UdevNotifier {


UdevNotifier::UdevNotifier(const QStringList &groups, QObject *parent)
    : QThread(parent)
    , d(new UdevNotifierPrivate)
{
    // register types needed for signals and slots
    qRegisterMetaType<UdevNotifier::Action>("UdevNotifier::Action");
    qRegisterMetaType<Device>("Device");

    d->groups = groups;
    d->udev = udev_new();

    if (!d->udev) {
        printf("Can't create udev\n");
        exit(1);
    }

    // TODO group monitoring goes here
    d->udevMonitor = udev_monitor_new_from_netlink(d->udev, "udev");

    if (d->udevMonitor) {
        // start receiving events
        udev_monitor_enable_receiving(d->udevMonitor);
    } else {
        qDebug("FAILED UDEv MONITOR");
    }
}

UdevNotifier::~UdevNotifier()
{
    delete d;
}

UdevNotifier::Action UdevNotifier::actionFromString(const QString &actionStr)
{
    qDebug("[UdevNotifier::actionFromString]");
    qDebug() << actionStr;


    if (actionStr == "add") {
        return ADD;
    } else if (actionStr == "remove") {
        return REMOVE;
    } else {
        return NONE;
    }
}

void UdevNotifier::run()
{
    qDebug("[UdevNotifier::run]");
    d->exit = false;

    while (!d->exit) {
        // create the poll item
        pollfd items[1];
        items[0].fd = udev_monitor_get_fd(d->udevMonitor);
        items[0].events = POLLIN;
        items[0].revents = 0;

        // while there are hotplug events to process
        while (poll(items, 1, 50) > 0) {
            // XXX
            qDebug() << "hotplug[ " << items[0].revents << " ]";

            // receive the relevant device
            udev_device* dev = udev_monitor_receive_device(d->udevMonitor);
            if (!dev) {
                // error receiving device, skip it
                qDebug("error rcv device. Skip");
                continue;
            }

            // XXX
//             qDebug() << "hotplug[" << udev_device_get_action(dev) << "] " << udev_device_get_devnode(dev) << "," << udev_device_get_subsystem(dev) << "," << udev_device_get_devtype(dev);
            // emit the found device
            Q_EMIT udevEvent(actionFromString(udev_device_get_action(dev)), new Device(dev));

            // destroy the relevant device
            udev_device_unref(dev);

            // XXX
            qDebug("-> done");

            // clear the revents
            items[0].revents = 0;
        }
    }

    qDebug("-> OUT");
}

void UdevNotifier::stop()
{
    d->exit = true;
}

}
