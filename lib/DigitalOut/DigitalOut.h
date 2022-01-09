/**
 * Digital output pin driver - abstracts the LOW/HIGH values to service.
 *
 * to abstract the device name, copy this driver to it's own class and modify _device_name in init().
 */

#ifndef WEBBRICKS_DIGITALOUT_H
#define WEBBRICKS_DIGITALOUT_H

#include "../Device/Device.h"

class DigitalOut: public Device{
/**
 * In the example states below, will report status as '", "<device name>":"ON"' when state is LOW
 * and also set state to HIGH on service command: <BASE_URL>/command/<device name>/OFF
 *
 * The driver will power up in the OFF state (_current_state)
 */
private:
    String _device_name;          // is set in init() on power-up.
    String _LOW_STATE = "ON";     // how the device will report when the state is LOW.
    String _HIGH_STATE = "OFF";   // how the device will report when the state is HIGH.
    int _current_state = HIGH;    // default state on power-up.

public:
    DigitalOut(int _pin);
    void init(void);
    String name();
    String command_check(String target_device, String command);
    String device_status(void);
};

#endif //WEBBRICKS_DIGITALOUT_H
