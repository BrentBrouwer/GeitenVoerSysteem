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
    public:
        void WriteSerialMsg(const char* msg);

    protected:
        void OpenSerialPort();
        void CloseSerialPort();

    /*
        Variables
    */
    public:
        // Singleton instance
        static Serial_ESP32* s_Instance;
    private:
        const int m_BaudRate = 9600;
};
#endif