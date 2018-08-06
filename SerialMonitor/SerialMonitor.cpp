#include "SerialMonitor.h"

SerialMonitor::SerialMonitor(boolean isOn, boolean openSerial, uint16_t baudRate = 9600)
{
    this->_isOn = isOn;
    if (!isOn) {
        return;
    }
    Serial.begin(baudRate);
    this->log("Serial has been initialized", logType::OK);
    if (openSerial) {
        while(!Serial) {
        // waiting for serial open
        }
        this->log("Serial Monitor is already open", logType::OK);
    }
}

void SerialMonitor::changeLogStatus(boolean newStatus)
{
    if (this->_isOn && !newStatus) {
        this->log("Serial Monitor is now OFF", logType::OK);
    }
    this->_isOn = newStatus;
}

void SerialMonitor::log(String smg, logType logT = logType::NONE, boolean newLine = true)
{
    if (!this->_isOn) {
        return;
    }
    String toPrint = "";
    switch (logT)
    {
        case NONE:
            break;     
        case OK:    toPrint += "[+]";
            break;
        case BAD:   toPrint += "[-]";
            break;
        case ERROR: toPrint += "[ERROR]";
            break;
    }
    toPrint += " ";
    toPrint += msg;
    if (newLine) {
        Serial.println(toPrint);
    } else {
        Serial.print(toPrint);
    } 
}