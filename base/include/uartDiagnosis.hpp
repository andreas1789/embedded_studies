#ifndef B2B47C23_E496_4C22_8CA0_19B6D7883BAF
#define B2B47C23_E496_4C22_8CA0_19B6D7883BAF
#include "types.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    class UartDiagnosis
    {
    public:
        UartDiagnosis(::peripherals::Uart uart);
        ~UartDiagnosis();

        void registerService(uint8_t sId, void (*callback)());
        uint8_t receiveSId();
        void processService();

    private:
        static constexpr uint8_t MAX_SERVICES = 10; // adjust if needed
        void (*_callbacks[MAX_SERVICES])();
        uint8_t _sIds[MAX_SERVICES];
        uint8_t _numServices;

        ::peripherals::Uart& _uart;

        List<uint8_t, 5> _serviceQueue;

        uint8_t _isValid(uint8_t sId);
    };
}

#endif /* B2B47C23_E496_4C22_8CA0_19B6D7883BAF */
