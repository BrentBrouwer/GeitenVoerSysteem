#ifndef Serial_h
#define Serial_h

class Serial
{
    private:
        /* data */
    public:
        Serial(/* args */);
        ~Serial();

    public:
        void LogMessage(const char* msg);

    protected:
        void OpenSerialPort();
        void CloseSerialPort();
};
#endif