#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "ESP8266WiFi.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rMotor = AFMS.getMotor(1), *lMotor = AFMS.getMotor(2);

const char* ssid = "MERCURY";
const char* password = "";

WiFiServer wifiServer(80);


void setup() {
  Serial.begin(115200);
  delay(500);

  AFMS.begin();           // Initialize motors as stopped while waiting for WiFi
  lMotor->setSpeed(0);
  rMotor->setSpeed(0);
  lMotor->run(FORWARD);
  rMotor->run(FORWARD);
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000); 
    Serial.println("Connecting...");
  }

  Serial.print("Connected to WiFi. IP: ");
  Serial.println(WiFi.localIP()); 

  wifiServer.begin();
}

void loop() {

  int lSpeed = 0;
  int rSpeed = 0;
  
  WiFiClient client = wifiServer.available();

  if(client) {
    while(client.connected()) {
      if(client.available()) {
        while(client.available() > 0) {
          char c = client.read();
          Serial.write(c);
  
          switch(c) {
            case 'w':
             lSpeed += 10;
             rSpeed += 10;
             break;
  
            case 's':
             lSpeed -= 10;
             rSpeed -= 10;
             break;
  
            case 'd':
             lSpeed += 10;
             rSpeed -= 10;
             break;
  
            case 'a':
             lSpeed -= 10;
             rSpeed += 10;
             break;
  
            default:
             Serial.println("Character Unrecognized");
             break;
          }
        }
        lSpeed = min(lSpeed, 255);
        lSpeed = max(lSpeed, 0);
        rSpeed = min(rSpeed, 255);
        rSpeed = max(rSpeed, 0);
      
        client.print("lSpeed: ");
        client.print(lSpeed);
        client.print("  -  rSpeed: ");
        client.println(rSpeed);        
        
        lMotor->setSpeed(lSpeed);
        rMotor->setSpeed(rSpeed);
      }
      delay(10);
    }
    
    client.stop();
    Serial.println("Client disconneted");

    lSpeed = 0;
    rSpeed = 0;

    lMotor->setSpeed(lSpeed);
    rMotor->setSpeed(rSpeed);
  }

  delay(10);
}
