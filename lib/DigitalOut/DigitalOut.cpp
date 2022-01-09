/**
 * Abstracts Digital Output pins
 *
 * 2/11/2021 - Created.
 */

#include "DigitalOut.h"

#include <Arduino.h>

DigitalOut::DigitalOut(int pin) : Device::Device(pin) {      // base class Device assigns pin to class variable _pin
    init();
}

void DigitalOut::init() {
    String tmp = String(_pin);
    _device_name = String("DigitalOut_" + tmp);
    digitalWrite(_pin,_current_state);
    pinMode(_pin,OUTPUT);
}

String DigitalOut::name() {
    return _device_name;
}

String DigitalOut::command_check(String target_device, String command) {
    if ( target_device == _device_name ) {
        if(_HIGH_STATE == command) {
            digitalWrite(_pin,HIGH);
            _current_state = HIGH;
            return String(",\"Command Status\":\"Set " + _device_name + " to " + String(_HIGH_STATE) + "\"");
        } else if(_LOW_STATE == command) {
            digitalWrite(_pin,LOW);
            _current_state = LOW;
            return String(",\"Command Status\":\"" + _device_name + " was set to " + String(_LOW_STATE) + "\"");
        } else {
            return String(",\"Command Status\":\"Parameter error for device " + _device_name + ".\"");
        }
    }
    return "";  // not our device
}

String DigitalOut::device_status() {
    if(_current_state == LOW) {
        return String(",\"" + _device_name + "\":\"" + String(_LOW_STATE) + "\"");
    }
    return String(",\"" + _device_name + "\":\"" + String(_HIGH_STATE) + "\"");
}
