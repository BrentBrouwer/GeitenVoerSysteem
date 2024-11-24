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
        static void LogMessage(const char* msg);
        static void LogMessageWithTimestamp(const char* msg);

    private:
        void WriteMessageToSerialPort(const char* msg);
    /*
        Variables
    */
    private:
        static ESP32_Log s_Instance;
        static const char m_STX = 2;
        static const char m_ETX = 3;
};
#endif