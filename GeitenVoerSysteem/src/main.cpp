#include <Arduino.h>
#include "Logging/Logging.h"
#include "Motor/MotorControl.h"

#pragma region Fields
// Status LED
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// Motor A
#define MOTOR_A_ENABLE 4
#define MOTOR_A_BACKWARD 18
#define MOTOR_A_FORWARD 19

// Motor A
#define MOTOR_B_ENABLE 0
#define MOTOR_B_BACKWARD 0
#define MOTOR_B_FORWARD 0
#pragma endregion

#pragma region Definitions
void LedStatusControl();
#pragma endregion

void setup()
{
    SetupLogging(9600);

    // Status LED
    pinMode(STATUS_LED_PIN, OUTPUT);

    LogMessage("Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:
    LedStatusControl();
}

// put function definitions here:
void LedStatusControl()
{
    int now = millis();
    if ((now - m_LastStatusChange) > 500)
    {
        m_LastStatusChange = now;
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    }
}