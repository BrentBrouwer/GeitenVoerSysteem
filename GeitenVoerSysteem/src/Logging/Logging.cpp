#include "Logging.h"
#include <Arduino.h>

bool Logging::s_LogEnabled = false;

void Logging::SetupLogging(int baudRate, bool enabled)
{
    Logging::s_LogEnabled = enabled;
    if (enabled)
    {
        Serial.begin(baudRate);
    }
}

void Logging::LogMessage(const char* msg, bool newLine)
{
    if (Logging::s_LogEnabled)
    {
        if (newLine)
        {
            Serial.println(msg);
        }
        else
        {
            Serial.print(msg);
        }
    }
}