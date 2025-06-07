AsyncEspWebServer::AsyncEspWebServer(int portNr, const char* ssid, const char* password, const char* domainName = NULL)
{
    // if (domainName != NULL)
    // {
    //     SetupDomainName();
    // }
    GetMacAdress();
    ConnectToLocalNetwork();
}

void AsyncEspWebServer::GetMacAdress()
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

void WifiServerESP::ConnectToLocalNetwork()
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