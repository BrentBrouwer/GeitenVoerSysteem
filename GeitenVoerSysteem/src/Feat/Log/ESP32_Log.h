#ifndef ESP32_Log_h
#define ESP32_Log_h

#include "../../Board/Serial/Serial.h"

class ESP32_Log
: Serial_ESP32
{
    /*
        Constructor
    */
    public:
        ESP32_Log();
        ~ESP32_Log();

    /*
        Methods
    */
    public:
        void LogMessage(const char* msg);
        void LogMessageWithTimestamp(const char* msg);

    private:
        void WriteMessageToSerialPort(const char* msg);
    /*
        Variables
    */
    private:
        const char m_STX = 2;
        const char m_ETX = 3;
};
#endif