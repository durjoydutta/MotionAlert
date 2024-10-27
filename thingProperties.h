// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "342ef11b-ad51-41d9-82cf-70eb7c019b1a";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onBulbChange();
void onBuzzerChange();
void onMotionControlChange();

CloudLight bulb;
CloudMotionSensor motionSensor;
CloudSwitch buzzer;
CloudSwitch motionControl;
CloudTemperatureSensor temperature;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(bulb, READWRITE, ON_CHANGE, onBulbChange);
  ArduinoCloud.addProperty(motionSensor, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(buzzer, READWRITE, ON_CHANGE, onBuzzerChange);
  ArduinoCloud.addProperty(motionControl, READWRITE, ON_CHANGE, onMotionControlChange);
  ArduinoCloud.addProperty(temperature, READ, ON_CHANGE, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
