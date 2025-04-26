#ifndef LOGGING

#define LOGGING

static void SetupLogging(int baudRate, bool enabled);
static void LogMessage(const char* msg);
static bool s_LogEnabled;

#endif // LOGGING