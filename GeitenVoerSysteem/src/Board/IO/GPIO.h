/*

    GPIO handler for the ESP32 Dev Board

*/

#ifndef GPIO_h
#define GPIO_h
class GPIO
{
    /*
        Constructor
    */
    public:
        GPIO();
        ~GPIO();

    /*
        Methods
    */
    public:
        void StatusLedControl();

    private:
        void InputInit();
        void OutputInit();

    /*
        Variables
    */
    private:
        // LED Status
        const unsigned long STATUS_LED_PERIOD_TIME = 2000;    // 0.5 Hz
        unsigned long m_LastStateChange = 0;
};
#endif