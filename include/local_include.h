/*
 * @TODO - set your controller name and IP address. The Name will be returned in the status data
 */
constexpr auto NAME = "Example Project";;
IPAddress ip(192, 168, 1, 106);

/**
 * @TODO - want debugging data to the serial port? Set the logs you want to see
 */
int LogLevel = 4;  /* 0 for no serial logs
                      1 - error
                      2 - warning plus 1 (error)
                      3 - info plus 1 and 2
                      4 - WiFi Connection plus 1-3
                      5 - command parsing plus 1-3
                      6 - devices plus 1-3

/**
 * @TODO - set your reset pin - one of the problems with WiFi is if the connection is dropped for any reason the
 *         Arduino hangs and should reset itself to power-on state in case of being in mid-process with a valve open
 *         or pump running but also because reconnection to the WiFi is not automatic. It must be reinitialized.
 *         I usually use Pin 13 and wire it to the reset pin. RESET pin is set LOW on WiFi connection failure.
 *         THERE MUST BE A JUMPER BETWEEN THE RESET PIN AND ARDUINO PIN 3 (RESET BAR)
  */
int RESET = 13;

/**
 * @TODO - set the port number for the service to run on, default is the HTTP standard port 80
 */

int PORT = 80;

/**
 * @TODO - Include your device driver libraries here. See README in the ~/lib for information creating your own drivers.
 */
#include <Tank.h>
#include <Pump.h>

/**
 * @TODO create an object for each device and an array to hold them here for global scope.
 *
 *       The device array is assigned in local_setup(). In this Example Project, there is hardware for 4 digital
 *       inputs and 4 digital outputs. The inputs are connected to float switches and the outputs to a relay to
 *       power a pump or enable a flow switch. There is a description of the project in the main README.md
 *
 */

Device *deviceA[8];             // Device is base class of all devices - define an array of your devices
Tank d0 = Tank(0);    // digital input from pin D0
Tank d1 = Tank(1);    // digital input from pin D1
Tank d2 = Tank(2);    // digital input from pin D2
Tank d3 = Tank(3);    // digital input from pin D3
Pump d4 = Pump(4);  // digital output to pin D4
Pump d5 = Pump(5);  // digital output to pin D5
Pump d6 = Pump(6);  // digital output to pin D6
Pump d7 = Pump(7);  // digital output to pin D7