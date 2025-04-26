#include "Logging.h"
#include <Arduino.h>

void SetupLogging(int baudRate)
{
    Serial.begin(baudRate);
}

void LogMessage(const char* msg)
{
    Serial.println(msg);
}