#ifndef UDEVNOTIFIER_H
#define UDEVNOTIFIER_H

#include "udevnotifier_global.h"

#include <QtCore/QThread>



namespace UdevNotifier {

class Device;
class UdevNotifierPrivate;

/**
 * @class UdevNotifier
 * @brief The UdevNotifier class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * This class watches the given groups from udev and notifies their actions
 */
class UDEVNOTIFIERSHARED_EXPORT UdevNotifier : public QThread
{
    Q_OBJECT

public:
    enum Action {
        ADD,
        REMOVE,
        NONE
    };
    Q_ENUM(Action)

    UdevNotifier(const QStringList &groups, QObject *parent = nullptr);
    ~UdevNotifier();

    /** stops the polling for devices */
    void stop();

Q_SIGNALS:
    void udevEvent(UdevNotifier::Action action, Device *device);

protected:
    void run() override final;

private:
    Action actionFromString(const QString &actionStr);

    UdevNotifierPrivate * const d;
};

}

Q_DECLARE_METATYPE(UdevNotifier::UdevNotifier::Action)

#endif // UDEVNOTIFIER_H


