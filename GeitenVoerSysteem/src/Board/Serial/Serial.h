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
        Serial_ESP32(int baudRate);
        ~Serial_ESP32();

    /*
        Methods
    */
    protected:
        void WriteSerialMsg(const char* msg);
        void OpenSerialPort();
        void CloseSerialPort();

    /*
        Variables
    */
    private:
        const int m_BaudRate = 9600;
};
#endif