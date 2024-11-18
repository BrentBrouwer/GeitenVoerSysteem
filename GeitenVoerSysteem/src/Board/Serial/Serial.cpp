// #ifdef ESP32_Serial_h
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
    LogMessage("Close serial port");
    Serial.end();
}

void Serial_ESP32::LogMessage(const char* msg)
{
    Serial.println(msg);
}

void Serial_ESP32::LogMessageWithTimestamp(const char* msg)
{
    Serial.println(printf("%i: %s", millis(), msg));
}
// #endif