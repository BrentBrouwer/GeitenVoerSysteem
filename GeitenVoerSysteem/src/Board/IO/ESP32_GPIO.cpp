// #ifdef ESP32_GPIO_h
#include "ESP32_GPIO.h"
#include <Arduino.h>

#define PIN_STATUS_LED 2

/*
    Constructor
*/
GPIO::GPIO()
{
    InputInit();
    OutputInit();
}

GPIO::~GPIO()
{

}

/*
    Methods
*/
void GPIO::InputInit()
{
    
}

void GPIO::OutputInit()
{
    pinMode(PIN_STATUS_LED, OUTPUT);
}

void GPIO::StatusLedControl()
{
    unsigned long currentTicks = millis();

    if ((currentTicks - m_LastStateChange) > (STATUS_LED_PERIOD_TIME / 2))
    {
        digitalWrite(PIN_STATUS_LED, !digitalRead(PIN_STATUS_LED) ? HIGH : LOW);
        m_LastStateChange = currentTicks;
    }
}
// #endif