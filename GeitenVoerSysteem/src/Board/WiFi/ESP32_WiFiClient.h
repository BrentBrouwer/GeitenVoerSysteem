#ifndef ESP32_WiFiClient_h
#define ESP32_WiFiClient_h

#include "WiFi.h"
#include "../../Feat/Log/ESP32_Log.h"

class ESP32_WiFiClient
: ESP32_Log
{
    /*
        Constructor
    */
    public:
        ESP32_WiFiClient(const char* hostName, const char* password);
        ~ESP32_WiFiClient();

    /*
        Methods
    */
    public:
        void CheckConnection();
        void WriteData(const char* msg);
    private:
        void StartConnection();

    /*
        Variables
    */
    public:
        bool IsConnected = false;

    private:
        const char* m_SSID;
        const char* m_Password;
        int m_LastConnectionUpdate = 0;
};
#endif