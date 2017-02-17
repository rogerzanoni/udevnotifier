#include <QtCore/QCoreApplication>

// #include <UdevNotifier>
#include <../include/UdevNotifier>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdevNotifier::UdevNotifier udevNot(QStringList() << "hidraw");

    return a.exec();
}

