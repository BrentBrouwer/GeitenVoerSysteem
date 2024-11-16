#ifdef Serial_h
#include "Serial.h"
#include "Arduino.h"

/*
    Constructor
*/
Serial::Serial()
{
    OpenSerialPort();
}

Serial::~Serial()
{
    LogMessage("Close serial port");
    CloseSerialPort();
}

/*
    Methods
*/
void Serial::OpenSerialPort()
{
    Serial.begin(BaudRate);
    delay(10);
    LogMessage("Serial port opened");
}

void Serial::CloseSerialPort()
{
    
}

void Serial::LogMessage(const char* msg)
{
    Serial.println(msg);
}
#endif