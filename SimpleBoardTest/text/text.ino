
// VERSION 0.1

// ----- CONFIG
    // VALUES
    static boolean status = true;

    // PC LOGS
    const boolean serialStatus = true;
    const uint16_t baudRate = 9600;


void ledBlink(uint16_t ON, uint16_t OFF, bool status = true) {
    while (status) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(ON);
        digitalWrite(LED_BUILTIN, LOW);
        delay(OFF);
    }
}
// ------ END CONFIG

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(baudRate);
    ledBlink(150, 150);       // wait until serial has been open
    while(!Serial) {
        Serial.println("[+] Serial is now active!");
        ledBlink(0, 0, false);
    }
    
}


void loop() {

}
