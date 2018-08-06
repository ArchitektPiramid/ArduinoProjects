#ifndef __SERIAL_MONITOR_H
#define __SERIAL_MONITOR_H

#include "Arduino.h"

enum logType {
    NONE,
    OK,
    BAD,
    ERROR      
}

class SerialMonitor
{
private:
    boolean _isOn;
    uint16_t _baudRate;

public:
    SerialMonitor(boolean isOn, baudRate = 9600);
};

#endif