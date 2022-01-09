/*
  Arduino WiFi Rev 2

  Provides a port 80 http service that an external server can poll to read data, or submit
  commands to connected devices that do some action, like water a plant or turn on sprinkler.

  To do this, the code below creates a simple web server on the configured static IP address.

  Directing a web browser to the static IP, ie http://192.168.1.104 would return a json string
  with the state of each configured pinout on the arduino board.
    {"Controller":"Garden_2,"free_ram":"1002","PinOut_2":"1","PinOut_3":"1","PinOut_5":"1","PinOut_6":"1"}
    -- in english for this board, all relays are off

  If I want to turn relay 6 ON for example http://192.168.1.104/command/PinOut_6/0 returns:
    {"Controller":"Garden_2,"free_ram":"1002","command_status":"PinOut_6 returns OK"}

  A subsequent call to returns:
    {"Controller":"Garden_2,"free_ram":"1002","PinOut_2":"1","PinOut_3":"1","PinOut_5":"1","PinOut_6":"0"}

  To turn off the relay again:  http://192.168.1.104/command/PinOut_6/1 returns:
    {"Controller":"Garden_2,"free_ram":"1002","command_status":"PinOut_6 returns OK"}

  04/12/2021 - Rick Welch - rick_welch@me.com - Created

*/

#include <Arduino.h>
#include <WiFiNINA.h>

#include "wifi_secrets.h"       // copy from wifi_secrets.h-example and modify for your network

char ssid[] = WIFI_SSID;        // your network SSID (name)
char pass[] = WIFI_PASS;        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;               // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
int indx1 = 0;                  // used to parse command line
int indx2 = 0;                  // used to parse command line
String target_device;           // command target device name
String arguments;               // the remainder of the URL request after target_device

#include "local_include.h"      // copy from local_include.h-example and modify for your devices

WiFiServer server(PORT);

int freeRam() {
    extern int __heap_start, * __brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}


void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    // print the WiFi signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
    // print where to go in a browser:
    Serial.print("To access this controller open a browser to http://");
    Serial.println(ip);
}

void setup() {

    #include "local_setup.h"    // copy from local_setup.h and modify for your devices

    if (LogLevel > 0) {
        Serial.begin(9600);         // initialize serial communication if logging
        Serial.print("System: ");   // announce the system name
        Serial.println(NAME);
    }

    target_device = ""; // name of the device when command given
    arguments = "";  // the remainder of the HTML request string sent as argument(s) to device - both parsed below

    pinMode(LED_BUILTIN, OUTPUT);      // set the builtin LED pin mode

    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        if (LogLevel > 0) Serial.println("Communication with WiFi module failed!");
        while (true);          // die()
    }

    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        if (LogLevel > 1) Serial.println("----> Firmware upgrade available <----");
    }

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        if (LogLevel == 4) {
            Serial.print("Attempting to connect to WiFi Network: ");
            Serial.println(ssid);                   // print the network name (SSID);
        }
        WiFi.config(ip);
        status = WiFi.begin(ssid, pass);
        // wait 10 seconds for connection:
        delay(10000);
    }
    server.begin();                           // start the web server on port 80
    if (LogLevel == 4) printWifiStatus();                       // you're connected now, so print out the status
    if (LogLevel > 2) Serial.println("System Ready");
}


void loop() {

    if (WiFi.status() != WL_CONNECTED) {
        /* if this check were not here the Arduino board would hang forever should the WiFi connection
         *  break for some reason. This checks the WiFi status then sets pin 13 to LOW to reset the
         *  Arduino after delaying for 2 minutes. The delay is in case the network is down.
         *
         *     *** There must be a jumper between pin 13 and RESET on the Arduino WiFi for this to work.
         */
        if (LogLevel > 0) {
            Serial.print("WiFi Connection Lost - delay two minutes to reset. status:");
            Serial.println(WiFi.status());
        }
        WiFi.end();
        delay(120000);
        pinMode(RESET,OUTPUT);
        digitalWrite(RESET,LOW);
    }
    WiFiClient client = server.available();   // listen for incoming clients

    if (client) {                     // if you get a client,
        if (LogLevel == 4) Serial.println("new client");          // print a message out the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                if (LogLevel == 4) Serial.write(c);                   // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {

                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:application/json");
                        client.println();
                        long rssi = WiFi.RSSI();
                        client.print("{\"Controller\":\"");
                        client.print(NAME);
                        client.print("\",\"RSSI\":\"");
                        client.print(rssi);
                        client.print(" dBm\"");
                        client.print(",\"free_ram\":\"");
                        client.print(freeRam());
                        client.print("\"");

                        if(target_device.equals("") == false){
                            for (int j = 0; j < sizeof(deviceA)/sizeof(deviceA[0]); j++) {
                                client.print(deviceA[j]->command_check(target_device, arguments));
                            }
                            target_device = "";
                        }
                        for (int i = 0; i < sizeof(deviceA)/sizeof(deviceA[0]); i++) {
                            client.print(deviceA[i]->device_status());
                        }
                        // The HTTP response ends with another blank line:
                        client.println("}");
                        // we're done - break out of the response loop:
                        break;
                    } else {    // if you got a newline, first parse, then clear currentLine:
                        if (currentLine.startsWith("GET /command/")) { // got a command for us?
                            indx1  = currentLine.indexOf("/", 14);
                            indx2 = currentLine.lastIndexOf(" ");
                            target_device = currentLine.substring(13, indx1);
                            indx1++;
                            arguments = currentLine.substring(indx1, indx2);
                            if (LogLevel == 5) {
                                Serial.print("currentLine: "); Serial.println(currentLine);
                                Serial.print("target_device: "); Serial.print(target_device);
                                Serial.print(", arguments: "); Serial.println(arguments);
                            }
                        }
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // close the connection:

        client.stop();
        if (LogLevel == 4) Serial.println("client disonnected");
    }
}
