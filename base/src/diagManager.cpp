#include "../include/diagManager.hpp"

namespace services
{
    DiagManager::DiagManager(UartDiagnosis diagnosis) : _uartDiagnosis(diagnosis) {}
    DiagManager::~DiagManager() {}

    void DiagManager::activateDiagnosis()
    {
        if (_currentState == State::Off)
        {
            _currentState = State::WaitForCommand;
        }
    }

    void DiagManager::checkInbox()
    {
        _uartDiagnosis.receiveSId();
        // todo 1. timeout
        // todo if something received
        _currentState = State::BusyRunningCommand;
    }

    void DiagManager::run()
    {
        switch (_currentState)
        {
        case State::Off:
            break;

        case State::WaitForCommand:
            checkInbox();
            break;

        case State::BusyRunningCommand:
            _uartDiagnosis.processService();
            // todo check if finshed, then switch state
            _currentState = State::Response;
            break;

        case State::Response:
            // logger("job done")
            _currentState = State::Off;
            break;

        default:
            break;
        }
    }
}
