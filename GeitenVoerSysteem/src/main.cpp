#include <Arduino.h>

// Properties
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// put function declarations here:
void LedStatusControl();

void setup()
{
    pinMode(STATUS_LED_PIN, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    LedStatusControl();
    sleep(1);
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