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

        void registerService(uint8_t id, void (*callback)());
        void tick();

    private:
        static constexpr uint8_t MAX_SERVICES = 10; // adjust if needed
        void (*_callbacks[MAX_SERVICES])();
        uint8_t _sIds[MAX_SERVICES];
        uint8_t _numServices;

        void _runCommand(uint8_t id, uint8_t* payload, uint8_t len);

        ::peripherals::Uart& _uart;

        void _feedByte(uint8_t b);
    };
}

#endif /* B2B47C23_E496_4C22_8CA0_19B6D7883BAF */
