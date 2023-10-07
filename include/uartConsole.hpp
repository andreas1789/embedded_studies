#include "types.hpp"
#include "gpio.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    class UartConsole : public ::peripherals::Uart
    {
    private:
        uint8_t bufferRx[256];

    public:
        UartConsole(uint32_t baudrate, uint8_t pinTx, uint8_t pinRx);
        ~UartConsole();
        void send(char msg[], uint32_t len);
        void receive(char msg[]);
    };
}