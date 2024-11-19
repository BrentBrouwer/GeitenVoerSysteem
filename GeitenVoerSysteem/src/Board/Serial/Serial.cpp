// #ifdef ESP32_Serial_h
#include "Serial.h"
#include <Arduino.h>

#define BaudRate 115200

/*
    Constructor
*/
Serial_ESP32::Serial_ESP32(int baudRate)
: m_BaudRate(baudRate)
{
    s_Instance = new Serial_ESP32(baudRate);
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
    Serial.begin(m_BaudRate);
    delay(10);
}

void Serial_ESP32::CloseSerialPort()
{
    Serial.end();
}

void Serial_ESP32::WriteSerialMsg(const char* msg)
{
    Serial.println(msg);
}
// #endif