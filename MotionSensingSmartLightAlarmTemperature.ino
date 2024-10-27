#include "arduino_secrets.h"
#include "thingProperties.h"
#include "DHT.h"

#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int relayPin = 18;   // Pin for the relay controlling the AC bulb
const int buzzerPin = 23;  // Pin for the buzzer
const int motionSensorPin = 4;  // Pin for the motion sensor

bool motionDetected = false; // Flag to track if motion is already detected
bool manualControl = false;  // Flag to track if the light was manually controlled

unsigned long firstMotionTime = 0;  // Timer for tracking the first time of a motion from off state
unsigned long buzzerStartTime = 0;  // Timer for the buzzer
unsigned long buzzerDelay = 500;    // Buzzer beeps for 0.5 seconds
unsigned long relayStartTime = 0;   // Timer for the relay (light)
unsigned long relayDelay = 30000;   // Light stays on for 30 seconds
unsigned long buzzerWindow = 5000;  // Time window for buzzer sound on new movement
unsigned long totalOnTime = 0;      // Timer for tracking total Relay on time

void setup() {
  dht.begin();
  Serial.begin(9600); 

  pinMode(relayPin, OUTPUT);        
  pinMode(buzzerPin, OUTPUT);       
  pinMode(motionSensorPin, INPUT);  

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  motionControl = false;
  ArduinoCloud.printDebugInfo();
  delay(5000);
}

void loop() {
  ArduinoCloud.update();

  float temp = dht.readTemperature();
  if (!isnan(temp)) {
    temperature = temp;
    Serial.println(temp);
  }
  int sensorValue = digitalRead(motionSensorPin);
  
  if (motionControl) {
    motionSensor = sensorValue;  // Update motion state in the cloud
  }
  
  unsigned long currentTime = millis();

  if (motionControl && sensorValue == 1) {  // Motion detected
    if (!motionDetected || (currentTime - buzzerStartTime >= buzzerWindow)) { 
      if (!motionDetected) {
        firstMotionTime = currentTime;
        motionDetected = true;
        manualControl = false;  // Reset manual control if motion starts
      }
      Serial.println("New Motion Detected!!");
      relayStartTime = currentTime;  // Reset relay timer when motion is detected

      // Buzzer logic: buzz if new motion or after the window period
      digitalWrite(buzzerPin, HIGH);  // Turn buzzer on
      buzzer = 1;
      buzzerStartTime = currentTime;  // Reset buzzer timer
    }

    // Check if buzzer time is over (buzz for xx seconds)
    if (currentTime - buzzerStartTime >= buzzerDelay) {
      digitalWrite(buzzerPin, LOW);  // Turn buzzer off after buzzerDelay
      buzzer = 0;
    }

    // Keep the light on
    digitalWrite(relayPin, HIGH);
    bulb = 1;
  }

  // If the relay is on, ensure it turns off after 30 seconds (only if not manually controlled)
  if (motionDetected && !manualControl && currentTime - relayStartTime >= relayDelay) {
    digitalWrite(relayPin, LOW);  // Turn the relay off after xx seconds
    bulb = 0;
    totalOnTime = currentTime - firstMotionTime;  // Calculate the total time the relay was on
    Serial.print("Light stayed on for: ");
    Serial.print(totalOnTime / 1000);  // Convert milliseconds to seconds
    Serial.println(" seconds");
    motionDetected = false;  // Reset motion detection flag
  }

  delay(250);  // Polling delay
}

void onBulbChange() {
    if (bulb == 1) {
        digitalWrite(relayPin, HIGH); // Turn the relay (bulb) on
        manualControl = true;  // Light turned on manually
    } else {
        digitalWrite(relayPin, LOW); // Turn the relay (bulb) off
        manualControl = false;
    }
}

void onBuzzerChange() {
    if (buzzer == 1) {
        digitalWrite(buzzerPin, HIGH);
        delay(1500); // Buzzer on for 1.5 seconds
        digitalWrite(buzzerPin, LOW);
        buzzer = 0;
        ArduinoCloud.printDebugInfo();
    } else {
        digitalWrite(buzzerPin, LOW);
    }
}

void onMotionControlChange() {
    Serial.print("Motion Sensor is turned ");
    String sensorStatus = (motionControl == 1) ? "on" : "off";
    Serial.println(sensorStatus);
    if (motionControl == 0) {
        motionSensor = 0;
    }
}
