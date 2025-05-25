#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

#include <WiFi.h>
#include "../Motor/MotorControl.h"
#include "../WiFi/WifiServer/WifiServerESP.h"

class BusinessLogic
{
    private:
        /* data */
    public:
        BusinessLogic(MotorControl* motorControl);
        void CheckMessage(ClientMsg clientData);

    private:
        void SendHtmlPage(WiFiClient client);

    public:
        static int s_MaxRunTime;

    private:
        // References
        MotorControl* m_MotorControl;

        // HTML Commands
        const String StartFeeding = "StartFeeding";
        const String StopFeeding = "StopFeeding";

        // HTML Page
        const String html_DocType = "<!doctype html>";
        const String html_Html = "<html lang=\"en-US\">";
        const String html_HtmlEnd = "</html>";

        const String html_Head = "<head><title>Geitjes</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<link rel=\"icon\" href=\"data:,\">";
        const String html_HeadEnd = "</head>";

        const String html_Style = "<style>";
        const char* html_ImageSourceHappy = "https://i.pinimg.com/originals/3a/ee/8d/3aee8d3cf15482a8972195ef398a081a.jpg";
        const char* html_ImageSourceSad = "https://images.fineartamerica.com/images/artworkimages/mediumlarge/1/sad-goat-ezume-images.jpg";
        const String html_StyleEnd = "</style>";

        const String html_BodyEnd = "</body>";
};
#endif