#ifndef DF567B41_9200_4290_954E_F7444CD325DB
#define DF567B41_9200_4290_954E_F7444CD325DB
#include "types.hpp"
#include "gpio.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    class UartConsole
    {
    private:
        uint8_t bufferRx[256];
        peripherals::Uart& _uart;

    public:
        UartConsole(peripherals::Uart& uart);
        ~UartConsole();
        void send(const char *msg);
        void receive(char msg[]);
    };
    extern UartConsole logger;
}

#endif /* DF567B41_9200_4290_954E_F7444CD325DB */
