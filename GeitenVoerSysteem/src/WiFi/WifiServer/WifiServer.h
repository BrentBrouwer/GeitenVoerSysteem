#include <SPI.h>
#include <WiFi.h>

class WifiServer
{
    public:
        WifiServer(int portNr, const char* ssid, const char* password, const char* domainName = NULL);
        ClientMsg GetConnectedClient();
    
    private:
        void SetupDomainName();
        void ConnectToLocalNetwork();
        void HandleIncomingMsg();
        
    private:
        WiFiServer m_WifiServer;
        const int m_PortNr;
        const char* m_SSID;
        const char* m_Password;
        const char* m_DomainName;

        
};

struct ClientMsg
{
    WiFiClient Client;
    String Message;
    int ConnectionTime;
};