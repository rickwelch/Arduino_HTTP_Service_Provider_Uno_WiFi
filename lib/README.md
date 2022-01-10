## Included drivers

- Device
    - Base class for all device drivers.
    - Is instantiated with an argument _pin which usually means the IO pin but could really be anything
    - Derived classes must contain 4 methods
        - init() - initializes the device on powerup
        - name() - returns the name of the device, usually class name plus the pin, ie pump_3 or tank_1
        - status() - returns information from the device
        - command_check(device_name,command) - when a command is sent, the code loops through the array of devices and calls this method. If current device is the target_device, the action is taken.
        
- DigitalIn
    - Reads a digital input
    - To be used as a starting point for your device, copy and rename to reflect device
    - Abstracts device status in each state, on, off, OK, fault, etc.
    - Methods
        - init() - sets the _pin to INPUT mode with a pull-up resistor
        - name() - returns DigitalIn_{_pin}
        - status() - returns string "Digital_1":"1 for HIGH, 0 for LOW"
        - command_check() - returns empty string, read only device
        
- DigitalOut
    - Sets the state HIGH or LOW of an output pin
    - To be used as a starting point for your device, copy and rename to reflect device
    - Abstracts device status in each state, on, off, OK, fault, etc.
    - Methods
        - init() - sets the _pin to OUTPUT mode
        - name() - returns DigitalOut_{_pin}
        - status() - returns string "DigitalOut_1":"current state of the output, 1 or 0"
        - command_check(target_device,command) - If device is the target set _pin to HIGH if command=1 or to LOW if command=0

- Pump
    - Duplicate of DigitalOut. D4-D7 drive the pump relays. 
    - Class name changed, modified init() method for new name. Updated Pump.h to proper abstraction ( ON, OFF ).
    
- Tank
    - Duplicate of DigitalIn. D0-D3 connected to float switch, HIGH when level low.
    - Class name changed, modified init() method for new name. Updated Tank.h for proper abstraction ( OK, LOW ).
    
----
### More Information
This project is described in detail on the [JSON_Example_Project](https://rickwelch.github.io/JSON_Example_Project/) page.

These drivers were built from code in the  [Arduino-Drivers](https://github.com/rickwelch/Arduino-Drivers) library. Check the library for more drivers and information on how to write custom drivers. 
