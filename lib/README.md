This project is described in detail on the [JSON_Example_Project](https://rickwelch.github.io/JSON_Example_Project/) page.

- These drivers were built starting with the [Arduino-Drivers](https://github.com/rickwelch/Arduino-Drivers) library. The Device, DigitalIn, and DigitalOut drivers were copied directly.

    - The Tank driver is a direct copy of the DigitalIn driver since D0 - D3 are used as inputs for float switches. The class name was changed, the proper name was set in the init() method and the LOW and HIGH parameters were changed in the class include file.

    - The Pump dirver is a direct copy of the DigitalOut driver D4-D7 are connected to relays that power pumps. Again the only changes made were the class name, the driver name in the init() method and the parameters in the .h file.

See the [Arduino-Drivers](https://github.com/rickwelch/Arduino-Drivers) for more drivers and information on how to write custom drivers. 
