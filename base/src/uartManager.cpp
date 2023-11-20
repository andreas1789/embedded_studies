#include "../include/uartManager.hpp"

namespace services
{
    UartManager::UartManager() : fUartConsole_(::services::UartConsole(115200, 2, 3)),
                                 fUartDiagnosis_(::services::UartDiagnosis())
    {
        state_ = UartStates::kUartOff;
    }

    void UartManager::run()
    {
        char frame;
        fUartConsole_.receiveByte(frame);

        switch (state_)
        {
        case UartStates::kUartOff:
            UartSessionControl ctrl = static_cast<UartSessionControl>(frame);

            if (ctrl == UartSessionControl::kConsole)
                state_ = UartStates::kUartConsole;

            else if (ctrl == UartSessionControl::kDiag)
                state_ = UartStates::kUartDiagOpen;

            break;

        case UartStates::kUartConsole:
            // run console();
            state_ = UartStates::kUartOff;
            break;

        case UartStates::kUartDiagOpen:
            // wait for length of messages to be received
            state_ = UartStates::kUartDiagData;
            break;

        case UartStates::kUartDiagData:
            // receive all data
            state_ = UartStates::kUartOff;

        default:
            break;
        }
    }

}