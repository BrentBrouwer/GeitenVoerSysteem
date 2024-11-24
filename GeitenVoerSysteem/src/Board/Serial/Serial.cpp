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
    // s_Instance = new Serial_ESP32(baudRate);
    if (!Serial.available())
    {
        OpenSerialPort();
    }
}

Serial_ESP32::~Serial_ESP32()
{
    // CloseSerialPort();
}

/*
    Methods
*/
void Serial_ESP32::OpenSerialPort()
{
    Serial.begin(m_BaudRate);
    // while (!Serial.available())
    // {
    //     delay(10);
    // }
    delay(10);
    WriteSerialMsg("Port opened");
}

void Serial_ESP32::CloseSerialPort()
{
    WriteSerialMsg("Close port");
    Serial.end();
}

void Serial_ESP32::WriteSerialMsg(const char* msg)
{
    Serial.println(msg);
}
// #endif