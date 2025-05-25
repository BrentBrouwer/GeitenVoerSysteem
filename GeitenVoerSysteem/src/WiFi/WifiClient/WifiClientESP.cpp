#include "WifiClientESP.h"

WifiClientESP::WifiClientESP()
{
}

void WifiClientESP::SendResponse(WiFiClient client, bool succes)
{
    client.println(succes ? "HTTP/1.1 200 OK" : "HTTP/1.1 400 BAD REQUEST");
}