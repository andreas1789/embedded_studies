#ifndef A0B59A6A_6745_496B_BFEA_0AFC42F1AA14
#define A0B59A6A_6745_496B_BFEA_0AFC42F1AA14

#include "uartDiagnosis.hpp"

using namespace types;

namespace services
{
    class DiagManager
    {
    public:
        enum class State
        {
            Off,
            WaitForCommand,
            BusyRunningCommand,
            Response
        };

    private:
        ::services::UartDiagnosis& _uartDiagnosis;
        State _currentState;

    public:
        DiagManager(UartDiagnosis diagnosis);
        ~DiagManager();

        void activateDiagnosis();          // Method to trigger the API call
        void checkInbox();
        void receiveCommand(char command); // Method to receive a command from UART
        void commandFinished();            // Method to indicate that the command execution is finished
        void responseSent();               // Method to indicate that the response has been sent over UART
        void run();                        // Method to run the command manager
    };
}

#endif /* A0B59A6A_6745_496B_BFEA_0AFC42F1AA14 */
