/**
 * Directly copied from the DigitalOut driver in this library: https://github.com/rickwelch/Arduino-Drivers
 * Changed name to Pump_<pin> in the init() method.
 * Set reporting as OFF and ON for states HIGH and LOW respectively below
 */

#ifndef WEBBRICKS_UNO_WIFI_PUMP_H
#define WEBBRICKS_UNO_WIFI_PUMP_H


#include "../Device/Device.h"

class Pump: public Device{

private:
    String _device_name;
    String _LOW_STATE = "ON";
    String _HIGH_STATE = "OFF";
    int _current_state = HIGH;

public:
    Pump(int _pin);
    void init(void);
    String name();
    String command_check(String target_device, String command);
    String device_status(void);
};


#endif //WEBBRICKS_UNO_WIFI_PUMP_H
