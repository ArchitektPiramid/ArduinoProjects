// VERSION 0.1

#include <SimpleDHT.h>   // DHT sensor by Winlin
#include <stdio.h>
#include <DS1302.h>

// ----- CONFIG
    #define BAUD_RATE 9600

    // PINS
    #define pinD_DHT 7
    const int kCePin   = 4;  // Chip Enable
    const int kIoPin   = 2;  // Input/Output
    const int kSclkPin = 3;  // Serial Clock

    // CLASSES
    SimpleDHT11 DHT;
    DS1302 rtc(kCePin, kIoPin, kSclkPin);


void ledBlink(uint16_t ON, uint16_t OFF, uint16_t times = 2) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(ON);
    digitalWrite(LED_BUILTIN, LOW);
    delay(OFF);
}

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
  }

void printTime() {
  Time t = rtc.time();

  const String day = dayAsString(t.day);
  char buf[50];
  snprintf(buf, sizeof(buf),  "%04d-%02d-%02d %02d:%02d:%02d",
  
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.println(buf);
}
// ------ END CONFIG

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);       // Init board blink led
    Serial.begin(BAUD_RATE);            // Init serial monitor
  
    while(!Serial) {
        // Wait until terminal has been open
    }
    Serial.println("[+] Serial Monitor succesfully initialized!");
}


void loop() {

unsigned char temperature = 0;
unsigned char humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = DHT.read(pinD_DHT, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
   char buf[100];
   Time t = rtc.time();
  snprintf(buf, sizeof(buf),  "%04d-%02d-%02d %02d:%02d,%02d,%02d",
  
           t.yr, t.mon, t.date,
           t.hr, t.min, temperature, humidity);

  Serial.println(buf);        

  
  delay(2 * 1000);

    // id, date, temp, hum, foto
}