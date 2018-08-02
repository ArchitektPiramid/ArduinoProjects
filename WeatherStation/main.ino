// VERSION 0.1

#include <SimpleDHT.h>   // DHT sensor by Winlin
#include <stdio.h>
#include <DS1302.h>
#include <SPI.h>
#include <SD.h>

// ----- CONFIG
    #define BAUD_RATE 9600
    #define SAVE_EVERY_MIN 10
    // PINS
    #define pinD_DHT 7
    #define pin_PRES A6
    const int kCePin   = 4;  // Chip Enable
    const int kIoPin   = 2;  // Input/Output
    const int kSclkPin = 3;  // Serial Clock

    // CLASSES
    SimpleDHT11 DHT;
    DS1302 rtc(kCePin, kIoPin, kSclkPin);
    File myFile;

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

String getFullTime() {
  Time t = rtc.time();

  const String day = dayAsString(t.day);
  char buf[50];
  snprintf(buf, sizeof(buf),  "%04d-%02d-%02d %02d:%02d:%02d",
  
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  return buf;
}

String getDateString() {
  Time t = rtc.time();

  const String day = dayAsString(t.day);
  char buf[12];
  snprintf(buf, sizeof(buf),  "%04d-%02d-%02d",
           t.yr, t.mon, t.date);

  return buf;
}
// ------ END CONFIG

void setup() {
    pinMode(pin_PRES, INPUT);           // for photoresistor
    pinMode(LED_BUILTIN, OUTPUT);       // Init board blink led
    Serial.begin(BAUD_RATE);            // Init serial monitor
  
    while(!Serial) {
        // Wait until terminal has been open
    }
    Serial.println("[+] Serial Monitor succesfully initialized!");

    if (!SD.begin(A0)) {
      Serial.println("initialization failed!");
      return;
  }
  Serial.println("[+] SD Card initialization done.");
}

void saveToSD(String time, int8_t temp, uint8_t hum) {
  String a = time;
  a += ",";
  a += temp;
  a += ",";
  a += hum;
  myFile = SD.open("teeest.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(a);
    myFile.close();
    Serial.print("[+] Added to file: ");
    Serial.println(a);
  }
}


void loop() {

  unsigned char temperature = 0;
  unsigned char humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = DHT.read(pinD_DHT, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
 // Serial.println(getDateString());
  
  //Serial.println(getFullTime());
  saveToSD(getFullTime(), temperature, humidity);


  delay(SAVE_EVERY_MIN * (60000));

    // id, date, temp, hum, foto
}

float getSunPrec() {
  int value = analogRead(pin_PRES);
  return (map(value, 0, 1023, 1000, 0) / 10.0);
}