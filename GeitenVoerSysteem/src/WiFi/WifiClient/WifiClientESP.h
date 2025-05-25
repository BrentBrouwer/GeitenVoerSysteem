#ifndef WIFI_CLIENT_ESP_H
#define WIFI_CLIENT_ESP_H

#include "WiFi.h"

class WifiClientESP
{
    public:
        WifiClientESP(); // Constructor

    public:
        WiFiClient m_Client;
};
#endif