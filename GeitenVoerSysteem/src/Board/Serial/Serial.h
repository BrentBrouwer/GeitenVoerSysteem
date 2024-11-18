/*

    Serial communication handler for the ESP32 Dev Board

*/

#ifndef ESP32_Serial_h
#define ESP32_Serial_h

class Serial_ESP32
{
    /*
        Constructor
    */
    public:
        Serial_ESP32();
        ~Serial_ESP32();

    /*
        Methods
    */
    public:
        void LogMessage(const char* msg);
        void LogMessageWithTimestamp(const char* msg);

    protected:
        void OpenSerialPort();
        void CloseSerialPort();

    /*
        Variables
    */
};
#endif