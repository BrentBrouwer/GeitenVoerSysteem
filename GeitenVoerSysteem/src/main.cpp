#include <Arduino.h>
#include "Board/ESP32_Board.h"
#include "Feat/Log/ESP32_Log.h"

// Hardware
static ESP32_Board s_Board;

// Initialize Logging
ESP32_Log m_Log;

void setup()
{
    ESP32_Log::LogMessage("Program started");
    // Serial.println("Program started");

    // Initialize the hardware
}

void loop()
{
    s_Board.StatusLedControl();
    delay(10);
}