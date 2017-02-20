#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>

// #include <UdevNotifier>
#include <../include/UdevNotifier>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdevNotifier::UdevNotifier udevNot(QStringList() << "udev");
    udevNot.start();

    QTimer::singleShot(3000, [&udevNot] () {
        udevNot.stop();
    });

    return a.exec();
}

