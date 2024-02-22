#include "../include/uartDiagnosis.hpp"

namespace services
{
    UartDiagnosis::UartDiagnosis(::peripherals::Uart uart) : _uart(uart) {}
    UartDiagnosis::~UartDiagnosis() {}

    void UartDiagnosis::registerService(uint8_t sId, void (*callback)())
    {
        if (_numServices < MAX_SERVICES)
        {
            _callbacks[_numServices] = callback;
            _sIds[_numServices] = sId;
            _numServices++;
        }
    }

    void UartDiagnosis::processService()
    {
        char b0;
        // char b1;
        // char b2;
        // char b3;
       _uart.receiveByte(b0); 
       // _uart.receiveByte(b1); 
       // _uart.receiveByte(b2); 
       // _uart.receiveByte(b3); 

       // execute callback corresponding to sId b
       for (uint8_t i=0; i<_numServices; ++i)
       {
            if (b0 == _sIds[i])
            {
                _callbacks[i]();
                break;
            }
       }
    }
}