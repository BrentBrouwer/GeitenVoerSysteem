#include "WiFi.h"

class WifiClientESP
{
    public:
        WifiClientESP(); // Constructor
        void SendResponse(WiFiClient client, bool succes);

};