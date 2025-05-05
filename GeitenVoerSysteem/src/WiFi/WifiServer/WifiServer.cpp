#include "WifiServer.h"
#include <ESPmDNS.h>
#include "../../Logging/Logging.h"

WifiServer::WifiServer(int portNr, const char* ssid, const char* password, const char* domainName)
: m_PortNr(portNr)
, m_SSID(ssid)
, m_Password(password)
, m_DomainName(domainName)
{
    if (domainName != NULL)
    {
        SetupDomainName();
    }
    ConnectToLocalNetwork();
}

void WifiServer::SetupDomainName()
{
    // Set the Local Domain Name
    mdns_init();
    mdns_hostname_set(m_DomainName);
    mdns_instance_name_set(m_DomainName);


    char msg[64];
    sprintf(msg, "MDNS responder started at http://%s.local\n", m_DomainName);
    Logging::LogMessage(msg);

    // Hostname
    if (WiFi.mode(WIFI_STA) && WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE) && WiFi.setHostname(m_DomainName))
    {
        Logging::LogMessage("Host name: ", false);
        Logging::LogMessage(WiFi.getHostname());
    }
    else
    {
        Logging::LogMessage("Failed to set the host name");
    }
}

void WifiServer::ConnectToLocalNetwork()
{
    char msg[32];
    sprintf(msg, "Connect to %s", m_SSID);
    Logging::LogMessage(msg);

    WiFi.begin(m_SSID, m_Password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    // Create the server and start it
    m_WifiServer = WiFiServer(m_PortNr);
    m_WifiServer.begin(m_PortNr);
}

ClientMsg WifiServer::GetConnectedClient()
{
    ClientMsg newClient;
    newClient.Message = "";
    WiFiClient client = m_WifiServer.available();
    
    // Check if there is a new client and has some data
    if (client)
    {
        newClient.Client = client;
        newClient.ConnectionTime = millis();

        // Read the buffer
        newClient.Message = client.readStringUntil('\n');
    }

    return newClient;
}