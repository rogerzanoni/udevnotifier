#include "core.h"

#include "../include/Device"
#include "../include/UdevNotifier"

#include <QtCore/QDebug>


Core::Core(QObject *parent)
    : QObject(parent)
    , m_udevNotifier(new UdevNotifier::UdevNotifier(QStringList(), this))
{
    connect(m_udevNotifier, &UdevNotifier::UdevNotifier::udevEvent, this, &Core::onUdevEvent);

    m_udevNotifier->start();
}

Core::~Core()
{
}

void Core::onUdevEvent(UdevNotifier::UdevNotifier::Action action, UdevNotifier::Device *device)
{
    qDebug("[Core::onUdevEvent]");
}
