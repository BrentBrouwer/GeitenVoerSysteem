/*

    ESP32 Dev Board base functionalities

*/  

#ifndef ESP32Board_h
#define ESP32Board_h

#include "IO/GPIO.h"
#include "Serial/Serial.h"

class ESP32_Board 
: public GPIO
, public Serial_ESP32
{
    /*
        Constructor
    */
    public:
        ESP32_Board();
        ~ESP32_Board();
};
#endif