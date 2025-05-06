#include <Arduino.h>
#include "Wifi/WifiServer/WifiServer.h"
#include "Motor/MotorControl.h"

#pragma region Fields
// Status LED
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// Wifi handling
WifiServer* m_WifiServer;

// Feeding motor
#define MOTOR_A_ENABLE 4
#define MOTOR_A_BACKWARD 18
#define MOTOR_A_FORWARD 19
MotorControl* m_FeedMotor;
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
    m_WifiServer = new WifiServer(80, "24GHz_TestNetwork", "BloempotKapsel243", "test");
    // m_WifiServer = new WifiServer(80, "De Onderbroek Van Oma Rikie", "Gordijn564", "test");

    // Create the feeding motor
    m_FeedMotor = new MotorControl(MOTOR_A_ENABLE, MOTOR_A_FORWARD, MOTOR_A_BACKWARD, "FeedMotor");

    Serial.println("Setup complete");
}

void loop()
{
    // put your main code here, to run repeatedly:
    LedStatusControl();

    // Check for connected clients that have send a request
    ClientMsg newClient = m_WifiServer->GetConnectedClient();

    // Check for a valid message
    if (newClient.Message != NULL)
    {
        // 

        // Clear the response message
        newClient.Message = "";

        // Close the Connection
        newClient.Client.stop();
        Serial.println("Client disconnected");
    }

    // if (firstTime)
    // {
    //     firstTime = false;
    //     m_FeedMotor->MotorFullSpeed(true);
    //     delay(2000);
    //     m_FeedMotor->MotorStop();
    // }
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