#include <Arduino.h>

#pragma region PreProcessor
#define EnableLogging
#define BaudRate 115200
#pragma endregion

#pragma region Properties
#pragma endregion

#pragma region Function Declarations
void SetupSerial();
void SetupGpio();
void LogMessage(const char* msg);
#pragma endregion

#pragma region Program
void setup()
{
    SetupSerial();
    SetupGpio();
}

void loop()
{
    delay(10);
}
#pragma endregion

#pragma Region Methods
void SetupSerial()
{
    Serial.begin(BaudRate);
    delay(10);
    LogMessage("Serial port opened");
}

void SetupGpio()
{
    LogMessage("GPIO initialised");
}

void LogMessage(const char* msg)
{
    // #ifdef EnableLog
    Serial.println(msg);
    // #endif
}
#pragma endregion