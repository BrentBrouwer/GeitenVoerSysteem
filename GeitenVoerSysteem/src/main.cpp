#include <Arduino.h>
#include "Logging/Logging.h"
#include "Motor/MotorControl.h"

#pragma region Fields
// Status LED
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// Feeding motor
#define MOTOR_A_ENABLE 4
#define MOTOR_A_BACKWARD 18
#define MOTOR_A_FORWARD 19
MotorControl* m_FeedMotor;
#pragma endregion

#pragma region Definitions
void LedStatusControl();
#pragma endregion

bool firstTime = true;

void setup()
{
    Logging::SetupLogging(9600, true);

    // Status LED
    pinMode(STATUS_LED_PIN, OUTPUT);

    // Create the feeding motor
    m_FeedMotor = new MotorControl(MOTOR_A_ENABLE, MOTOR_A_FORWARD, MOTOR_A_BACKWARD, "FeedMotor");

    Logging::LogMessage("Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:
    LedStatusControl();

    if (firstTime)
    {
        firstTime = false;
        m_FeedMotor->MotorFullSpeed(true);
        delay(2000);
        m_FeedMotor->MotorStop();
    }
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