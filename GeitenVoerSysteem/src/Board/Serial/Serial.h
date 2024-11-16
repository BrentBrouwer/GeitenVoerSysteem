/*

    Serial communication handler for the ESP32 Dev Board

*/

#ifndef Serial_h
#define Serial_h

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

    protected:
        void OpenSerialPort();
        void CloseSerialPort();

    /*
        Variables
    */
};
#endif