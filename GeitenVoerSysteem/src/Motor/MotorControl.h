#ifndef MOTOR_CONTROL

#define MOTOR_CONTROL

enum Motors
{
    MotorA,
    MotorB
};

class MotorControl
{
    public:
        // Constructor
        MotorControl(Motors motor, int enablePin, int forwardPin, int backwardPin, const char* motorName);

        // Methods
        void MotorStop();
        void MotorFullSpeed(bool forward);
    
    private:
        // Methods
        bool EnableMotor(bool enable);
        bool ValidPins(int forwardPin, int backwardPin);

        // Fields
        const Motors m_SelectedMotor;
        const int m_EnablePin = 0;
        const int m_ForwardPin = 0;
        const int m_BackwardPin = 0;
        const char* m_MotorString;
};

#endif // MOTOR_CONTROL