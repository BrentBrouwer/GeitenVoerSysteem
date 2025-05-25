#include "BusinessLogic.h"

int BusinessLogic::s_MaxRunTime = 3000;

BusinessLogic::BusinessLogic(MotorControl* motorControl)
: m_MotorControl(motorControl)
{
    if (motorControl != nullptr)
    {
        m_MotorControl = motorControl;
    }
}

void BusinessLogic::CheckMessage(ClientMsg clientData)
{
    // Message content
    int startFeedingIndex = clientData.Message.indexOf(StartFeeding);
    int stopFeedingIndex = clientData.Message.indexOf(StopFeeding);

    // Motor Status
    bool motorRunning = m_MotorControl->IsMotorRunning();

    if (startFeedingIndex >= 0 && !motorRunning)
    {
        // Allowed to start feeding
        m_MotorControl->MotorFullSpeed(true);
    }
    else
    {        
        m_MotorControl->MotorStop();
    }

    SendHtmlPage(clientData.Client);
}

void BusinessLogic::SendHtmlPage(WiFiClient client)
{
    bool motorRunning = m_MotorControl->IsMotorRunning();

    // Doc Type-------------------------------------------------
    client.println(html_DocType);

    // Head-----------------------------------------------------
    // Header
    client.println(html_Head);
    client.println(html_Style);

    // Background image
    client.printf("body {background-image: url('%s');\n", html_ImageSourceHappy);
    client.println("background-size: cover;");
    client.println("background-repeat: none;}");

    // Text Color
    // client.printf("h1 {color: %s}\n", ledOnNow ? "green" : "red");

    client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.printf(".button { background-color: %s; border: 2px solid black; color: black; padding: 16px 40px;\n", motorRunning ? "red" : "green");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(html_StyleEnd);
    client.println(html_HeadEnd);
            
    // Body-----------------------------------------------------
    client.printf("<body><h1>%s</h1>\n", motorRunning ? "De geitjes zijn je eeuwig dankbaar voor de verlichting" : "Lul! Je hebt de verlichting uit gezet!");

    // Label
    // client.printf("<p1>LED status: %s</p1>\n", ledOn ? "aan" : "uit");

    // Button
    // The href property sets the addres
    client.printf("<p><a href=\"/LED/%s\"><button class=\"button\">%s voeren</button></a></p>\n", motorRunning ? StopFeeding : StartFeeding, motorRunning ? "Stop" : "Start");
    client.println(html_BodyEnd);

    // End Response---------------------------------------------
    client.println(html_HtmlEnd);
    client.println();
}