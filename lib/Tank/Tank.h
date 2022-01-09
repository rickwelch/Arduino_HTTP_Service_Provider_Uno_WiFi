/**
 * Directly copied from the DigitalIn driver in this library: https://github.com/rickwelch/Arduino-Drivers
 * Changed name to Tank_<pin> in the init() method.
 * Set reporting as LOW and OK for states HIGH and LOW respectively below
 */


#ifndef WEBBRICKS_UNO_WIFI_TANK_H
#define WEBBRICKS_UNO_WIFI_TANK_H

#include "../Device/Device.h"

class Tank: public Device {
private:
    String _device_name;
    String _LOW_STATE = "OK";
    String _HIGH_STATE = "LOW";

public:
    Tank(int pin);
    void init(void);
    String name();
    String command_check(String target, String command);
    String device_status(void);
};


#endif //WEBBRICKS_UNO_WIFI_TANK_H
