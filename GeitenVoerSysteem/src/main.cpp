#include <Arduino.h>
#include "Board/ESP32_Board.h"

// Hardware
static ESP32_Board s_Board;

void setup()
{
}

void loop()
{
    s_Board.StatusLedControl();
    delay(10);
}