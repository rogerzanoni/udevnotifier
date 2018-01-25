#include "device.h"
#include "udevnotifier.h"
#include "udevnotifier_p.h"


#include <libudev.h>
#include <monitor.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#include"webcam.h"
#include <QtCore/QDebug>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

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

    d->connectorTypes[DRM_MODE_CONNECTOR_Unknown]     = QString("unknown");
    d->connectorTypes[DRM_MODE_CONNECTOR_VGA]         = QString("VGA");
    d->connectorTypes[DRM_MODE_CONNECTOR_DVII]        = QString("DVI-I");
    d->connectorTypes[DRM_MODE_CONNECTOR_DVID]        = QString("DVI-D");
    d->connectorTypes[DRM_MODE_CONNECTOR_DVIA]        = QString("DVI-A");
    d->connectorTypes[DRM_MODE_CONNECTOR_Composite]   = QString("composite");
    d->connectorTypes[DRM_MODE_CONNECTOR_SVIDEO]      = QString("s-video");
    d->connectorTypes[DRM_MODE_CONNECTOR_LVDS]        = QString("LVDS");
    d->connectorTypes[DRM_MODE_CONNECTOR_Component]   = QString("component");
    d->connectorTypes[DRM_MODE_CONNECTOR_9PinDIN]     = QString("9-pin DIN");
    d->connectorTypes[DRM_MODE_CONNECTOR_DisplayPort] = QString("DP");
    d->connectorTypes[DRM_MODE_CONNECTOR_HDMIA]       = QString("HDMI-A");
    d->connectorTypes[DRM_MODE_CONNECTOR_HDMIB]       = QString("HDMI-B");
    d->connectorTypes[DRM_MODE_CONNECTOR_TV]          = QString("TV");
    d->connectorTypes[DRM_MODE_CONNECTOR_eDP]         = QString("eDP");
    d->connectorTypes[DRM_MODE_CONNECTOR_VIRTUAL]     = QString("Virtual");
    d->connectorTypes[DRM_MODE_CONNECTOR_DSI]         = QString("DSI");
    d->connectorTypes[DRM_MODE_CONNECTOR_DPI]         = QString("DPI");
}

UdevNotifier::~UdevNotifier()
{
    delete d;
}

UdevNotifier::Action UdevNotifier::actionFromString(const QString &actionStr)
{
    qDebug("[UdevNotifier::actionFromString]");
    qDebug() << actionStr;


    if (actionStr == QLatin1String("add")) {
        return ADD;
    } else if (actionStr == QLatin1String("remove")) {
        return REMOVE;
    } else {
        // not handled at the moment
        return NONE;
    }
}

void UdevNotifier::scan()
{
    struct udev *udev = d->udev;
    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "drm");
    udev_enumerate_add_match_sysname(enumerate, "card[0-9]-*");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *dev_list_entry;
    struct udev_device *dev;

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;

        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        if (!dev) {
            continue;
        }

        qDebug("[UdevNotifier::scan] Found display: %s", udev_device_get_sysname(dev));
        qDebug() << "[UdevNotifier::scan] xserver output name:" << displayOutputName(udev_device_get_sysname(dev));
        qDebug("[UdevNotifier::scan] enabled? %s", udev_device_get_sysattr_value(dev, "enabled"));

        if (QString(udev_device_get_sysattr_value(dev, "enabled")) == QLatin1String("enabled")) {
            Q_EMIT udevEvent(ADD, new Monitor(dev));
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "video4linux");
    udev_enumerate_scan_devices(enumerate);

    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;

        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        if (!dev) {
            continue;
        }

        qDebug("[UdevNotifier::scan] Found webcam: %s", udev_device_get_sysattr_value(dev, "name"));
        qDebug("[UdevNotifier::scan] node %s", udev_device_get_devnode(dev));

        Q_EMIT udevEvent(ADD, new Webcam(dev));

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
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
          //  qDebug() << "hotplug[ " << items[0].revents << " ]";

            // receive the relevant device
            udev_device* dev = udev_monitor_receive_device(d->udevMonitor);
            if (!dev) {
                // error receiving device, skip it
                qDebug("error rcv device. Skip");
                continue;
            }

            //qDebug() << "hotplug[" << udev_device_get_action(dev) << "] " << udev_device_get_devnode(dev) << "," << udev_device_get_subsystem(dev) << "," << udev_device_get_devtype(dev);
            // emit the found device
            if (udev_device_get_devtype(dev) == QLatin1String("drm_minor")) {
                Q_EMIT udevEvent(actionFromString(udev_device_get_action(dev)), new Monitor(dev));
            }

            if (udev_device_get_subsystem(dev) == QLatin1String("video4linux")) {
                Q_EMIT udevEvent(actionFromString(udev_device_get_action(dev)), new Webcam(dev));
            }
            // XXX
         //   qDebug("-> done");

            // clear the revents
            items[0].revents = 0;
        }
    }

  //  qDebug("-> OUT");
}

void UdevNotifier::stop()
{
    d->exit = true;
}

QString UdevNotifier::displayOutputName(const QString &udevName)
{
    QString card = udevName.left(udevName.indexOf("-"));
    QString drmConnectorType = udevName.mid(udevName.indexOf("-") + 1, udevName.lastIndexOf("-") - udevName.indexOf("-") - 1);
    QString cardNode = QString("/dev/dri/%1").arg(card);

    qDebug() << "[UdevNotifier::deviceXOutputName] card:" << card;
    qDebug() << "[UdevNotifier::deviceXOutputName] drm output name:" << drmConnectorType;
    qDebug() << "[UdevNotifier::deviceXOutputName] card node:" << cardNode;

    int fd = open(cardNode.toLatin1().data(), O_RDWR | O_CLOEXEC);

    if (fd < 0) {
        qDebug() << "[UdevNotifier::deviceXOutputName] cannot open";
        return QString();
    }


    drmModeRes *res = drmModeGetResources(fd);
    if (!res) {
        qDebug() << "[UdevNotifier::deviceXOutputName] cannot retrieve drm resrouces - error: " << errno;
        goto cleanupclose;
    }

    // find the connector
    for (int i = 0; i < res->count_connectors; ++i) {
        drmModeConnector *connector = drmModeGetConnector(fd, res->connectors[i]);
        if (!connector) {
            qDebug() << "[UdevNotifier::deviceXOutputName] cannot retrieve DRM connector" << res->connectors[i] << "error:" << errno;
            continue;
        }

        QString connectorType = d->connectorTypes[connector->connector_type];
        qDebug() << "[UdevNotifier::deviceXOutputName] connector found:" << connector->connector_id <<  "type:" << connectorType;

        if (connectorType == drmConnectorType) {
            // connector found, now find the crct
            if (connector->encoder_id) {
                qDebug() << "[UdevNotifier::deviceXOutputName] using encoder bound to the connector";
                drmModeEncoder *encoder = drmModeGetEncoder(fd, connector->encoder_id);

                if (encoder->crtc_id) {
                    int32_t crtc = encoder->crtc_id;
                    qDebug() << "[UdevNotifier::deviceXOutputName] found crtc:" << crtc << "name:" << displayOutputName(crtc);
                }

                drmModeFreeEncoder(encoder);
            } else {
                qDebug() << "[UdevNotifier::deviceXOutputName] no encoder bound to the connector";
                // XXX iterate over all global crtcs
            }
        }

        drmModeFreeConnector(connector);
    }

    drmModeFreeResources(res);

cleanupclose:
    close(fd);

    return QString();
}

QString UdevNotifier::displayOutputName(int32_t crtc)
{
    Display* display = XOpenDisplay(NULL);
    Window window = RootWindow(display, DefaultScreen(display));
    XRRScreenResources* screenRes = XRRGetScreenResources(display, window);
    QString outputName;

    for (int i = 0; i < screenRes->noutput; ++i) {
        XRROutputInfo *outputInfo = XRRGetOutputInfo(display, screenRes, screenRes->outputs[i]);
        qDebug() << "[UdevNotifier::displayOutputName] found output: " << outputInfo->name;

        for (int j = 0; j < outputInfo->ncrtc; ++j) {
            if (outputInfo->crtcs[j] == crtc) {
                qDebug() << "[UdevNotifier::displayOutputName] found crtc. Output name: " << outputInfo->name;
                outputName = outputInfo->name;
                break;
            }
        }

        XRRFreeOutputInfo(outputInfo);
    }

    XCloseDisplay(display);

    return outputName;
}

}
