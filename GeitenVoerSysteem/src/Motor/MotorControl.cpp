#include "MotorControl.h"
#include <Arduino.h>
#include "../Logging/Logging.h"

MotorControl::MotorControl(int enablePin, int forwardPin, int backwardPin, const char* motorName) : 
m_EnablePin(enablePin),
m_ForwardPin(forwardPin),
m_BackwardPin(backwardPin),
m_MotorString (motorName)
{
    if (ValidPins(forwardPin, backwardPin))
    {
        pinMode(enablePin, OUTPUT);
        pinMode(forwardPin, OUTPUT);
        pinMode(backwardPin, OUTPUT);
    }
}

void MotorControl::MotorStop()
{
    digitalWrite(m_ForwardPin, LOW);
    digitalWrite(m_BackwardPin, LOW);
    if (EnableMotor(false))
    {
        // LogMessage("Motor stopped");
    }
    else
    {
        // LogMessage("Failed to stop motor");
    }
}

void MotorControl::MotorFullSpeed(bool forward)
{
    char msg[64];
    sprintf(msg, "%s full speed %s", m_MotorString, forward ? "forward" : "backward");
    // LogMessage(msg);

    // Enable the drive
    if (EnableMotor(true))
    {
        if (forward)
        {
            // First disable backwards, then enable forwards
            digitalWrite(m_BackwardPin, LOW);
            delay(100);
            digitalWrite(m_ForwardPin, HIGH);
            // LogMessage("Forward complete");
        }
        else
        {
            // First disable forwards, then enable backwards
            digitalWrite(m_ForwardPin, LOW);
            delay(100);
            digitalWrite(m_BackwardPin, HIGH);
            // LogMessage("Backward complete");
        }
    }
}

bool MotorControl::EnableMotor(bool enable)
{
    if (m_EnablePin > -1)
    {
        digitalWrite(m_EnablePin, enable ? HIGH : LOW);
        bool enabled = digitalRead(m_EnablePin);

        char msg[64];
        sprintf(msg, "%s %s", m_MotorString, enabled ? "enabled" : "disabled");
        // LogMessage(msg);
        return enable == enabled;
    }
    return false;
}

bool MotorControl::ValidPins(int forwardPin, int backwardPin)
{
    bool valid = forwardPin > -1 && backwardPin > -1;
    char msg[32];
    sprintf(msg, "%s pins selected", valid ? "valid" : "invalid");
    // LogMessage(msg);
    return valid;
}