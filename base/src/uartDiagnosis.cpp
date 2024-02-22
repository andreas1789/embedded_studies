#include "../include/uartDiagnosis.hpp"

namespace services
{
    UartDiagnosis::UartDiagnosis(::peripherals::Uart uart) : _uart(uart) {}
    UartDiagnosis::~UartDiagnosis() {}

    uint8_t UartDiagnosis::_isValid(uint8_t sId)
    {
        (void)sId;
        return 1;
    }

    void UartDiagnosis::registerService(uint8_t sId, void (*callback)())
    {
        if (_numServices < MAX_SERVICES)
        {
            _callbacks[_numServices] = callback;
            _sIds[_numServices] = sId;
            _numServices++;
        }
    }

    uint8_t UartDiagnosis::receiveSId()
    {
        char b0;
        _uart.receiveByte(b0);

        uint8_t sId = (uint8_t)b0;
        if (_isValid(sId))
        {
            _serviceQueue.push(sId);
            return sId;
        }
        else
            return 0;
    }

    void UartDiagnosis::processService()
    {
        uint8_t queuedSId = _serviceQueue.pop();

        // execute callback corresponding to sId b
        for (uint8_t i = 0; i < _numServices; ++i)
        {
            if (queuedSId == _sIds[i])
            {
                _callbacks[i]();
                break;
            }
        }
    }
}