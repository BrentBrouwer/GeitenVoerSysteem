/*

    Serial communication handler for the ESP32 Dev Board

*/

#ifndef Serial_h
#define Serial_h

class Serial
{
    /*
        Constructor
    */
    public:
        Serial();
        ~Serial();

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