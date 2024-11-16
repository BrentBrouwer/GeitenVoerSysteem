// #ifdef Serial_h
#include "Serial.h"
#include <Arduino.h>

#define BaudRate 115200

/*
    Constructor
*/
Serial_ESP32::Serial_ESP32()
{
    OpenSerialPort();
}

Serial_ESP32::~Serial_ESP32()
{
    LogMessage("Close serial port");
    CloseSerialPort();
}

/*
    Methods
*/
void Serial_ESP32::OpenSerialPort()
{
    Serial.begin(BaudRate);
    delay(10);
    LogMessage("Serial port opened");
}

void Serial_ESP32::CloseSerialPort()
{
    
}

void Serial_ESP32::LogMessage(const char* msg)
{
    Serial.println(msg);
}
// #endif