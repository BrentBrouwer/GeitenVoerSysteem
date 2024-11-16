#ifndef ESP32Board_h
#define ESP32Board_h

#ifdef GPIO_h
#include "GPIO.h"
#endif
#ifdef SERIAL_h
#include "Serial.h"
#endif

class ESP32_Board 
: public GPIO
, public Serial
{
    private:

    public:
        ESP32_Board();
        ~ESP32_Board();
};
#endif