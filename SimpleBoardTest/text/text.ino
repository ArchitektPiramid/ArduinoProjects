
// VERSION 0.1

#include "SimpleDHT.h"   // DHT sensor by Winlin

// ----- CONFIG
    #define BAUD_RATE 9600
    #define DHTTYPE DHT11


void ledBlink(uint16_t ON, uint16_t OFF, uint16_t times = 2) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(ON);
    digitalWrite(LED_BUILTIN, LOW);
    delay(OFF);
}

// ------ END CONFIG

SimpleDHT11 dht11;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);       // Init board blink led
    Serial.begin(BAUD_RATE);            // Init serial monitor
  
    while(!Serial) {
        // Wait until terminal has been open
    }
    Serial.println("[+] Serial Monitor succesfully initialized!");
}


void loop() {
     byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(A6, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
