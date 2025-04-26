#include "Logging.h"
#include <Arduino.h>

void SetupLogging(int baudRate, bool enabled)
{
    s_LogEnabled = enabled;
    if (enabled)
    {
        Serial.begin(baudRate);
    }
}

void LogMessage(const char* msg)
{
    if (s_LogEnabled)
    {
        Serial.println(msg);
    }
}