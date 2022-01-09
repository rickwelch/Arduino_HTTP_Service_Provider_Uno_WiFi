- wifi_secrets.h

    - must contain your WiFi name and user password

- local_include.h 
    - contains all the declaration code needed before setup(). This includes including your device driver libraries and declaring them. There must be a driver for each device as a class the ~/lib directory.   

- local_setup.h
     - Contains code to be run during setup(). 
     - Here you build the device array. The code loops through this array for every HTTP request. If there are any arguments, they're parsed and passed to each device for action or to ignore after which each device is called to generate it's JSON status.
     - See the ~/lib directory for more information
     
