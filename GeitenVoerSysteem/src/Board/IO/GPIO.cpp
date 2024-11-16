/*

GPIO handler for the ESP32 Dev Board

*/
#ifdef GPIO_h
#include "GPIO.h"
#include "Arduino.h"

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
    PinMode(PIN_STATUS_LED, OUTPUT);
}

void GPIO::StatusLedControl()
{
    unsigned long currentTicks = millis();

    if ((currentTicks - m_LastStateChange) > (STATUS_LED_PERIOD_TIME / 2))
    {
        digitalWrite(StatusLedPin, !digitalRead(StatusLedPin) ? HIGH : LOW);
        m_LastStateChange = currentTicks;
    }
}
#endif