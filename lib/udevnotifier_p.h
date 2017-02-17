#ifndef UDEVNOTIFIER_P_H
#define UDEVNOTIFIER_P_H

#include <QtCore/QStringList>

namespace UdevNotifier {

class UdevNotifierPrivate
{
public:
    UdevNotifierPrivate() {}

    QStringList groups;
};

}

#endif // UDEVNOTIFIER_P_H
