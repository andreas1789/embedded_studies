#include "uartConsole.hpp"

namespace services
{
    UartConsole::UartConsole(peripherals::Uart &uart) : _uart(uart)
    {
    }

    UartConsole::~UartConsole() {}

    void UartConsole::send(const char *msg)
    {
        while (*msg)
            _uart.sendByte(*msg++);
    }

    void UartConsole::receive(char msg[])
    {
        msg[0] = '0';
    }
}