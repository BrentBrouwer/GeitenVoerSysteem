#include <SPI.h>
#include <WiFi.h>


struct ClientMsg
{
    WiFiClient Client;
    String Message;
    int ConnectionTime;
};

class WifiServer
{
    public:
        WifiServer(int portNr, const char* ssid, const char* password, const char* domainName = NULL);
        ClientMsg GetConnectedClient();
    
    private:
        void GetMacAdress();
        void SetupDomainName();
        void ConnectToLocalNetwork();
        void HandleIncomingMsg();
        
    private:
        WiFiServer m_WifiServer;
        const uint16_t m_PortNr;
        const char* m_SSID;
        const char* m_Password;
        const char* m_DomainName;
};