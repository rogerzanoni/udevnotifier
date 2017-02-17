#ifndef UDEVNOTIFIER_H
#define UDEVNOTIFIER_H

#include "udevnotifier_global.h"

#include <QtCore/QObject>


namespace UdevNotifier {

class UdevNotifierPrivate;

/**
 * @class UdevNotifier
 * @brief The UdevNotifier class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * This class watches the given groups from udev and notifies their actions
 */
class UDEVNOTIFIERSHARED_EXPORT UdevNotifier : public QObject // QThread?
{
    Q_OBJECT

public:
    UdevNotifier(const QStringList &groups, QObject *parent = nullptr);
    ~UdevNotifier();

private:
    UdevNotifierPrivate * const d;
};

}

#endif // UDEVNOTIFIER_H


