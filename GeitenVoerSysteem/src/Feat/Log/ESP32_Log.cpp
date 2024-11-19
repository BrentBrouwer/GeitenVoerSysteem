// #ifdef ESP32_Log_h
#include "ESP32_Log.h"
#include <Arduino.h>
// #include <cstdio>

/*
    Constructor
*/
ESP32_Log::ESP32_Log(/* args */)
: Serial_ESP32(115200)
{
}

ESP32_Log::~ESP32_Log()
{
}

/*
    Methods
*/
void ESP32_Log::LogMessage(const char* msg)
{
    WriteMessageToSerialPort(msg);
}

void ESP32_Log::LogMessageWithTimestamp(const char* msg)
{
    char* msgToSend;
    sprintf(msgToSend, "%i: %s", millis());
    WriteMessageToSerialPort(msgToSend);
}

void ESP32_Log::WriteMessageToSerialPort(const char* msg)
{
    char* msgToSend;
    sprintf(msgToSend, "%c%s%c", m_STX, msg, m_ETX);
    WriteSerialMsg(msgToSend);
}
// #endif