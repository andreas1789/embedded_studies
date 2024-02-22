#ifndef B2B47C23_E496_4C22_8CA0_19B6D7883BAF
#define B2B47C23_E496_4C22_8CA0_19B6D7883BAF
#include "types.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    static constexpr uint8_t MAX_SERVICES = 10; // adjust if needed
    void (*_callbacks[MAX_SERVICES])();
    uint8_t _sIds[MAX_SERVICES];
    uint8_t _numServices;

    class UartDiagnosis
    {
        public:
        UartDiagnosis(::peripherals::Uart uart);
        ~UartDiagnosis();

        void registerService(uint8_t sId, void (*callback)());
        void processService();

        private:
        ::peripherals::Uart _uart;


    };
}


#endif /* B2B47C23_E496_4C22_8CA0_19B6D7883BAF */
