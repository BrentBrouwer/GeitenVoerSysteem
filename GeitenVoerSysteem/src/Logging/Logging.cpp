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

void Logging::LogMessage(const char* msg)
{
    if (Logging::s_LogEnabled)
    {
        Serial.println(msg);
    }
}