#ifndef ASYNC_WIFI_SERVER_H
#define ASYNC_WIFI_SERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class AsyncWifiServer
{
public:
    AsyncWifiServer(const char *ssid, const char *password);

private:
    void ConnectToLocalNetwork();

private:
    AsyncWebServer *m_Server;
    const char *m_SSID;
    const char *m_PASSWORD;
};
#endif