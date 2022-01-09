/**
 * Digital input pin driver - abstracts the LOW/HIGH values to service.
 *
 * to abstract the device name, copy this driver to it's own class and modify _device_name in init().
 */

#ifndef WEBBRICKS_DIGITALIN_H
#define WEBBRICKS_DIGITALIN_H

#include "../Device/Device.h"

class DigitalIn: public Device {

/**
* In the example states below, will report status as '", "<device name>":"OK"' when state is LOW and "FAULT" when HIGH.
*/
private:
String _device_name;                // is set in init().
String _LOW_STATE = "OK";           // reports OK when state is LOW
String _HIGH_STATE = "FAULT";       // reports FAULT when state is HIGH

public:
DigitalIn(int pin);
void init(void);
String name();
String command_check(String target, String command);
String device_status(void);
};


#endif //WEBBRICKS_DIGITALIN_H
