#include <Arduino.h>
#include "Wifi/WifiServer/WifiServerESP.h"
#include "Wifi/WifiServer/AsyncWifiServer.h"
#include "Motor/MotorControl.h"
#include "BusinessLogic/BusinessLogic.h"


#pragma region Fields
// Status LED
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// Wifi handling
// WifiServerESP* m_WifiServer;
AsyncWifiServer* m_WifiServer;

// Feeding motor
#define MOTOR_A_ENABLE 4
#define MOTOR_A_BACKWARD 18
#define MOTOR_A_FORWARD 19
MotorControl* m_FeedMotor;

// Business Logic
BusinessLogic* m_BusinessLogic;
#pragma endregion

#pragma region Definitions
void SetupLogging();
void LedStatusControl();
#pragma endregion

bool firstTime = true;

void setup()
{
    SetupLogging();

    // Status LED
    pinMode(STATUS_LED_PIN, OUTPUT);

    // Create the WifiServer
    // m_WifiServer = new WifiServer(80, "24GHz_TestNetwork", "BloempotKapsel243", "test");
    // m_WifiServer = new WifiServer(80, "De Onderbroek Van Oma Rikie", "Gordijn564", "test");
    // m_WifiServer = new WifiServerESP(80, "vBakel", "1001100111");
    // m_WifiServer = new WifiServerESP(80, "Eenwieler", "Autoband");
    // m_WifiServer = new WifiServerESP(80, "24GHz", "123456789");
    // m_WifiServer = new AsyncWifiServer("vBakel", "1001100111");
    m_WifiServer = new AsyncWifiServer("24GHz", "123456789");

    // Create the feeding motor
    m_FeedMotor = new MotorControl(MOTOR_A_ENABLE, MOTOR_A_FORWARD, MOTOR_A_BACKWARD, "FeedMotor");

    // Create the business logic
    m_BusinessLogic = new BusinessLogic(m_FeedMotor);

    Serial.println("Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:
    LedStatusControl();

    /*
    // Check for connected clients that have send a request
    ClientMsg newClient = m_WifiServer->GetConnectedClient();

    // Check for a valid message
    if (newClient.Message != NULL)
    {
        // Get the IP-address of the connected client
        Serial.print(newClient.Client.remoteIP());
        Serial.println(" connected");

        // Response to the client
        m_WifiServer->SendResponseCode(newClient.Client, true);
        m_BusinessLogic->CheckMessage(newClient);

        // Clear the response message
        newClient.Message = "";

        // Close the Connection
        // newClient.Client.stop();
        Serial.println("Client disconnected");
    }
    */

    // ToDo: reset the button in the html page when the motor is stopped
    // Motor timeout control
    // m_FeedMotor->CheckMaxRunTime(BusinessLogic::s_MaxRunTime);
    if (m_FeedMotor->CheckMaxRunTime(BusinessLogic::s_MaxRunTime)) // && &newClient.Client != nullptr)
    // if (true)
    {
        // m_BusinessLogic->SendHtmlPage(newClient.Client);
        Serial.println("Motor stopped by timeout");
    }
}

// put function definitions here:
void SetupLogging()
{
    Serial.begin(9600);
    delay(100);

    // Below not working
    // while (!Serial.available())
    // {
    //     sleep(1);
    // }

    Serial.println("Serial monitor opened");
}

void LedStatusControl()
{
    int now = millis();
    if ((now - m_LastStatusChange) > 500)
    {
        m_LastStatusChange = now;
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    }
}