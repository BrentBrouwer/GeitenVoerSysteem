#ifndef MOTOR_CONTROL_H

#define MOTOR_CONTROL_H

class MotorControl
{
    public:
        // Constructor
        MotorControl(int enablePin, int forwardPin, int backwardPin, const char* motorName);

        // Methods
        void MotorStop();
        void MotorFullSpeed(bool forward);
        bool IsMotorRunning();
        bool CheckMaxRunTime(int maxRunTime = 3000);    // 3000 ms as default
    
    private:
        // Methods
        bool EnableMotor(bool enable);
        bool ValidPins(int forwardPin, int backwardPin);

        // FieldS
        const int m_EnablePin = 0;
        const int m_ForwardPin = 0;
        const int m_BackwardPin = 0;
        const char* m_MotorString;

        int m_StartTimeStamp = 0;
        int m_MaxRunTime = 0;
};

#endif // MOTOR_CONTROL