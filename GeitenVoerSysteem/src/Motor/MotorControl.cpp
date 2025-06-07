#include "MotorControl.h"
#include <Arduino.h>

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
    m_StartTimeStamp = 0;
    digitalWrite(m_ForwardPin, LOW);
    digitalWrite(m_BackwardPin, LOW);
    if (EnableMotor(false))
    {
        Serial.println("Motor stopped");
    }
    else
    {
        Serial.println("Failed to stop motor");
    }
}

void MotorControl::MotorFullSpeed(bool forward)
{
    char msg[64];
    sprintf(msg, "%s full speed %s", m_MotorString, forward ? "forward" : "backward");
    Serial.println(msg);

    // Enable the drive
    if (EnableMotor(true))
    {
        if (forward)
        {
            // First disable backwards, then enable forwards
            digitalWrite(m_BackwardPin, LOW);
            delay(100);
            digitalWrite(m_ForwardPin, HIGH);
            m_StartTimeStamp = millis();
            Serial.println("Forward complete");
        }
        else
        {
            // First disable forwards, then enable backwards
            digitalWrite(m_ForwardPin, LOW);
            delay(100);
            digitalWrite(m_BackwardPin, HIGH);
            m_StartTimeStamp = millis();
            Serial.println("Backward complete");
        }
    }
}

bool MotorControl::IsMotorRunning()
{
    // Check if the motor is enabled
    if (digitalRead(m_EnablePin))
    {
        // If either one of the pins are on, the motor is running
        return digitalRead(m_ForwardPin) || digitalRead(m_BackwardPin);
    }
    return false;
}

bool MotorControl::EnableMotor(bool enable)
{
    if (m_EnablePin > -1)
    {
        digitalWrite(m_EnablePin, enable ? HIGH : LOW);
        bool enabled = digitalRead(m_EnablePin);

        char msg[64];
        sprintf(msg, "%s %s", m_MotorString, enabled ? "enabled" : "disabled");
        Serial.println(msg);
        return enable == enabled;
    }
    return false;
}

bool MotorControl::ValidPins(int forwardPin, int backwardPin)
{
    bool valid = forwardPin > -1 && backwardPin > -1;
    char msg[32];
    sprintf(msg, "%s pins selected", valid ? "valid" : "invalid");
    Serial.println(msg);
    return valid;
}

/// @brief Controls the maximum runtime for a motor
/// @param maxRunTime 
/// @return true if motor was stopped due to a timeout, otherwise false
bool MotorControl::CheckMaxRunTime(int maxRunTime)
{
    int now = millis();
    if (IsMotorRunning() &&
        (now - m_StartTimeStamp) >= maxRunTime)
    {
        // Timeout expired, stop the motor
        MotorStop();
        return true;
    }
    return false;
}