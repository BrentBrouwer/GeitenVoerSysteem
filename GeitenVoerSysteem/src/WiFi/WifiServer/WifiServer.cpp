#include "WifiServer.h"
#include <ESPmDNS.h>
#include <esp_wifi.h>

WifiServer::WifiServer(int portNr, const char *ssid, const char *password, const char *domainName)
    : m_PortNr(portNr), m_SSID(ssid), m_Password(password), m_DomainName(domainName)
{
    if (domainName != NULL)
    {
        SetupDomainName();
    }
    GetMacAdress();
    ConnectToLocalNetwork();
}

void WifiServer::GetMacAdress()
{
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    if (ret == ESP_OK)
    {
        Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);
    }
    else
    {
        Serial.println("Failed to read MAC address");
    }
}

void WifiServer::SetupDomainName()
{
    // Domain name can only be used when the domain is registerd at a DNS

    // Set the Local Domain Name
    mdns_init();
    mdns_hostname_set(m_DomainName);
    mdns_instance_name_set(m_DomainName);
    Serial.printf("MDNS responder started at http://%s.local\n", m_DomainName);

    // Hostname
    if (WiFi.mode(WIFI_STA) && WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE) && WiFi.setHostname(m_DomainName))
    {
        Serial.printf("Hostname: %s\n", WiFi.getHostname());
    }
    else
    {
        Serial.println("Failed to set the host name");
    }
}

void WifiServer::ConnectToLocalNetwork()
{
    Serial.printf("Connect to '%s'\n", m_SSID);

    WiFi.begin(m_SSID, m_Password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    Serial.println("Connected");

    // Create the server and start it
    m_WifiServer.begin(m_PortNr);
    Serial.print("Server adress: ");
    Serial.println(WiFi.localIP());
}

ClientMsg WifiServer::GetConnectedClient()
{
    ClientMsg newClient;
    newClient.Message = "";
    WiFiClient client = m_WifiServer.available();

    // Check if there is a new client and has some data
    if (client)
    {
        Serial.print("New client: ");
        Serial.println(client.remoteIP());

        newClient.Client = client;
        newClient.ConnectionTime = millis();
        // Serial.printf("Connected at: %lu\n", newClient.ConnectionTime);

        // Read the buffer
        newClient.Message = client.readStringUntil('\n');
        Serial.print("New msg: ");
        Serial.println(newClient.Message);
    }

    return newClient;
}