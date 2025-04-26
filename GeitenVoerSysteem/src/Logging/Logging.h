#ifndef LOGGING

#define LOGGING

class Logging
{
    public:
        static void SetupLogging(int baudRate, bool enabled);
        static void LogMessage(const char* msg);
    private:  
        static bool s_LogEnabled;
};

// static void SetupLogging(int baudRate, bool enabled);
// static void LogMessage(const char* msg);
// static bool s_LogEnabled;

#endif // LOGGING