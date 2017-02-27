# UDevNotifier

This Qt/C++ class was created in order to receive notifications from the UDEV event system. It uses Qt signals to notify when
a device is inserted, removed or moved.

The `UDevNotifier` class has the role of notifying when an event is received. So you'll need to create this object in order to start listening for events.

Whenever a Udev event is received, the `UDevNotifier::udevEvent` signal is emitted along with the `UDevNotifier::Action` and a pointer to the `UDevNotifier::Device` class detected.


See the `example` folder for how to use the library.
