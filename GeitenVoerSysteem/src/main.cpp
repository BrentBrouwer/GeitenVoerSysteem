#include <Arduino.h>
#include <tuple>
#include <string>
#include <bits/stdc++.h>

#pragma region Enum
enum Motors
{
    MotorA,
    MotorB
};
#pragma endregion

#pragma region Fields
// Status LED
#define STATUS_LED_PIN 2
int m_LastStatusChange = 0;

// Motor A
#define MOTOR_A_ENABLE 4
#define MOTOR_A_BACKWARD 18
#define MOTOR_A_FORWARD 19

// Motor A
#define MOTOR_B_ENABLE 0
#define MOTOR_B_BACKWARD 0
#define MOTOR_B_FORWARD 0
#pragma endregion

#pragma region Definitions
void LedStatusControl();

// Motors
void MotorStop(Motors motor);
void MotorFullSpeed(Motors motor, bool forward);
bool EnableMotor(Motors motor, bool enable);
std::tuple<int, int> GetDirectionPins(Motors motor);
bool ValidPins(int forwardPin, int backwardPin);
char* GetMotorString(Motors motor);
#pragma endregion

void setup()
{
    // Serial port
    Serial.begin(9600);
    Serial.println(" ");
    Serial.println("Start program");

    // Status LED
    pinMode(STATUS_LED_PIN, OUTPUT);
    
    // Motor A
    pinMode(MOTOR_A_ENABLE, OUTPUT);
    pinMode(MOTOR_A_BACKWARD, OUTPUT);
    pinMode(MOTOR_A_FORWARD, OUTPUT);

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("Start loop");

    // put your main code here, to run repeatedly:
    LedStatusControl();

    // Forward for 1000 ms
    Serial.println("Forward");
    MotorFullSpeed(MotorA, true);
    sleep(1000);

    // Stop for 1000 ms
    Serial.println("Stop1");
    MotorStop(MotorA);
    sleep(1000);

    // Backward for 1000 ms
    Serial.println("Backward");
    MotorFullSpeed(MotorA, false);
    sleep(1000);

    // Stop for 1000 ms
    Serial.println("Stop2");
    MotorStop(MotorA);
    sleep(1000);

    // Prevent high CPU-usage
    sleep(1);
}

// put function definitions here:
void LedStatusControl()
{
    int now = millis();
    if ((now - m_LastStatusChange) > 500)
    {
        m_LastStatusChange = now;
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    }
}

#pragma region Motor
/// @brief Stop a given motor
/// @param motor 
void MotorStop(Motors motor)
{
    // Get the correct pins
    int forwardPin, backwardPin;
    std::tie(forwardPin, backwardPin) = GetDirectionPins(motor);
    if (ValidPins(forwardPin, backwardPin))
    {
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, LOW);
        if (EnableMotor(motor, false))
        {
            Serial.println("Motor stopped");
        }
        else
        {
            Serial.println("Failed to stop motor");
        }
    }
}

/// @brief Run a motor at full speed
/// @param motor 
/// @param forward
void MotorFullSpeed(Motors motor, bool forward)
{
    char msg[64];
    sprintf(msg, "%s full speed %s", GetMotorString(motor), forward ? "forward" : "backward");
    Serial.println(msg);

    // Enable the drive
    if (EnableMotor(motor, true))
    {
        // Get the correct pins
        int forwardPin, backwardPin;
        std::tie(forwardPin, backwardPin) = GetDirectionPins(motor);

        if (ValidPins(forwardPin, backwardPin))
        {
            Serial.println("Select direction");

            if (forward)
            {
                Serial.println("Forward start");

                // First disable backwards, then enable forwards
                digitalWrite(backwardPin, LOW);
                sleep(10);
                digitalWrite(forwardPin, HIGH);
                Serial.println("Forward complete");
            }
            else
            {
                Serial.println("Backward start");

                // First disable forwards, then enable backwards
                digitalWrite(forwardPin, LOW);
                sleep(10);
                digitalWrite(backwardPin, HIGH);
                Serial.println("Backward complete");
            }
        }
    }
}

/// @brief Get the forward and backward pin of a given motor
/// @param motor 
/// @return ForwardPin, BackwardPin
std::tuple<int, int> GetDirectionPins(Motors motor)
{
    int forwardPin = -1;
    int backwardwardPin = -1;
    switch (motor)
    {
        case MotorA:
            forwardPin = MOTOR_A_FORWARD;
            backwardwardPin = MOTOR_A_BACKWARD;
            break;

        case MotorB:
            forwardPin = MOTOR_B_FORWARD;
            backwardwardPin = MOTOR_A_BACKWARD;
            break;
    
        default:
            break;
    }

    return std::make_tuple(forwardPin, backwardwardPin);
}

/// @brief Enable or disable a motor
/// @param motor 
/// @param enable
/// @return 
bool EnableMotor(Motors motor, bool enable)
{
    int enablePin = -1;
    switch (motor)
    {
        case MotorA:
            enablePin = MOTOR_A_ENABLE;
            break;
            
        case MotorB:
            enablePin = MOTOR_B_ENABLE;
            break;
    
        default:
            break;
    }

    if (enablePin > -1)
    {
        digitalWrite(enablePin, enable ? HIGH : LOW);
        bool enabled = digitalRead(enablePin);
        
        char msg[64];
        sprintf(msg, "%s %s", GetMotorString(motor), enabled ? "enabled" : "disabled");
        Serial.println(msg);
        return enabled;
    }
    return false;
}

bool ValidPins(int forwardPin, int backwardPin)
{
    bool valid = forwardPin > -1 && backwardPin > -1;
    char msg[32];
    sprintf(msg, "%s pins selected", valid ? "valid" : "invalid");
    Serial.println(msg);
    return valid;
}

char* GetMotorString(Motors motor)
{
    switch(motor)
    {
        case MotorA:
            return "MotorA";
            
        case MotorB:
            return "MotorB";

        default:
            return " ";
    }
}
#pragma endregion
