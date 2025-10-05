#include "../include/uartDiagnosis.hpp"
#include "uartConsole.hpp"

namespace services
{
    namespace
    {
        enum
        {
            ST_WAIT_START,
            ST_ID,
            ST_LEN,
            ST_PAYLOAD,
            ST_CHECKSUM
        };

        static uint8_t d_state = ST_WAIT_START;
        static uint8_t d_checksum = 0;
        static uint8_t d_cmd_id = 0;
        static uint8_t d_cmd_len = 0;
        static uint8_t d_payload[256];
        static uint8_t d_payload_pos = 0;
    }

    UartDiagnosis::UartDiagnosis(::peripherals::Uart uart) : _uart(uart) {}
    UartDiagnosis::~UartDiagnosis() {}

    void UartDiagnosis::registerService(uint8_t id, void (*callback)())
    {
        if (_numServices < MAX_SERVICES)
        {
            _callbacks[_numServices] = callback;
            _sIds[_numServices] = id;
            _numServices++;
        }
    }

    void UartDiagnosis::_runCommand(uint8_t id, uint8_t *payload, uint8_t len)
    {
        (void)len;
        switch (id)
        {
        case 1:
            if (payload[0] == 1)
            {
                GPIO_ODR |= GPIO_ODR_PIN(13);
            }
            else if (payload[0] == 2)
            {
                 GPIO_ODR &= ~GPIO_ODR_PIN(13);
            }
            break;

        default:
            
            break;
        }
    }

    void UartDiagnosis::tick()
    {
        char b;
        // while (_uart.receiveByte(b) == peripherals::Uart::Status::rx_available)
        // {
        //     _feedByte((uint8_t)(b));
        // }

        while (_uart.read(b))
        {
            _feedByte((uint8_t)b);
        }
        
    }

    void UartDiagnosis::_feedByte(uint8_t b)
    {
        switch (d_state)
        {
        case ST_WAIT_START:
            if (b == 0x55)
            {
                d_state = ST_ID;
                d_checksum = 0;
            }
            GPIO_ODR |= GPIO_ODR_PIN(13);
            break;
        case ST_ID:
            d_cmd_id = b;
            d_checksum = b;
            d_state = ST_LEN;
            break;
        case ST_LEN:
            d_cmd_len = b;
            d_checksum ^= b;
            d_state = ST_PAYLOAD;
            break;
        case ST_PAYLOAD:
            d_payload[d_payload_pos++] = b;
            d_checksum ^= b;
            if (d_payload_pos >= d_cmd_len)
            {
                d_state = ST_CHECKSUM;
            }
            break;
        case ST_CHECKSUM:
            if (b == d_checksum)
            {
                // Todo: handle command
            }
            else
            {
                services::logger.send("uartDiagnosis.cpp: checksum error");
            }
            d_state = ST_WAIT_START;
            break;
        default:
            d_state = ST_WAIT_START;
            break;
        }
    }
}