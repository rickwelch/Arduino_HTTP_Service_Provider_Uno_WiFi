/*
 * Base class for devices attached to qn Arduino controller - child classes must contain four methods:
 *     init() - which initializes the device
 *     name() - which returns the name of the device (see DigitalOut for example)
 *     device_status() - which returns a JSON string of any device information (see DigitalOut for example)
 *     command_check() - which checks to see if an action is required of the device (see DigitalOut for example)
 *
 * 2021-11-15 Rick Welch welch@webbricks.net - Created
 * 2021-11-29 Rick Welch welch@webbircks.net - Add some documentation
 */

#ifndef WEBBRICKS_ARDUINO_DEVICE_H
#define WEBBRICKS_ARDUINO_DEVICE_H
#include <Arduino.h>

class Device
{
protected:
    int _pin;
    String _device_name;

public:

    Device(int pin);
    virtual void init()=0;
    virtual String name()=0;
    virtual String device_status(void)=0;
    virtual String command_check(String target, String command)=0;
};


#endif //WEBBRICKS_ARDUINO_DEVICE_H
