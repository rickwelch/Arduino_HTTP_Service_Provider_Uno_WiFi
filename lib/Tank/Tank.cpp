/**
 * See Tank.h for more information
 */

#include "Tank.h"

Tank::Tank(int pin):  Device::Device(pin)
{
    init();
}

void Tank::init() {
    String tmp = String(_pin);
    _device_name = String("Tank_" + tmp);
    pinMode(_pin,INPUT_PULLUP);
}

String Tank::name() {
    return _device_name;
}

String Tank::command_check(String target, String command) {
    return "";    // read only device
}

String Tank::device_status() {
    int state = digitalRead(_pin);
    if(state == LOW){
        return String(",\"" + _device_name + "\":\"" + _LOW_STATE + "\"");
    }
    return String(",\"" + _device_name + "\":\"" + _HIGH_STATE + "\"");
}
