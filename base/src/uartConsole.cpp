#include "uartConsole.hpp"

namespace services
{
    UartConsole::UartConsole(uint32_t baudrate, uint8_t pinTx, uint8_t pinRx) : 
                                Uart(baudrate, pinTx, pinRx)
    {
    }

    UartConsole::~UartConsole(){}

    void UartConsole::send(char msg[], uint32_t len)
    {
        if (len <= 256)
        {
            uint32_t cursor  = 0;
            while (cursor  < len)
            {
                sendByte(msg[cursor]);
                cursor++;
            }
        }
    }

    void UartConsole::receive(char msg[])
    {
        msg[0] = '0';
    }
}