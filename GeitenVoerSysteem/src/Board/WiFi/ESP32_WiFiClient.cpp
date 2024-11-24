// #ifdef ESP32_WiFiClient_h
#include "ESP32_WiFiClient.h"

/*
    Constructor
*/
ESP32_WiFiClient::ESP32_WiFiClient(const char* hostName, const char* password)
{   
    // Immediately try to connect to the server
    StartConnection();
}

ESP32_WiFiClient::~ESP32_WiFiClient()
{
    WiFi.disconnect();
}

/*
    Methods
*/
void ESP32_WiFiClient::StartConnection()
{
    // Close the current connection for a restart
    WiFi.disconnect();

    // Try to connect
    WiFi.begin(m_SSID, m_Password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(5);
    }
    m_LastConnectionUpdate = millis();
    LogMessage("Connected");
}

void CheckConnection()
{
    // Check the Connection, otherwise reconnect
    if (!WiFi.isConnected())
    {
        WiFi.reconnect();
    }
}

void WriteData(const char* msg)
{
    
}



// #endif