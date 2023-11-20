#include "uartFrame.hpp"

namespace services
{

    UartFrameAepAdapter::UartFrameAepAdapter(uint8_t port, ::peripherals::Uart iUart) : _port(port),
                                                                                        _IUart(iUart)
    {
    }

    Std_ReturnType_t UartFrameAepAdapter::send()
    {
        //updateHeader();

        byte_t *buf = reinterpret_cast<byte_t *>(&txFrame);

        for (uint8_t i = 0U; i < (sizeof(txFrame.header) + UART_FRAME_DATA_LENGTH); ++i)
        {
            _IUart.sendByte(buf[i]);
        }

        return E_OK;
    }

    Std_ReturnType_t UartFrameAepAdapter::receive()
    {

        byte_t *buf = reinterpret_cast<byte_t *>(&rxFrame);

        for (uint8_t i = 0U; i < (sizeof(rxFrame.header) + UART_FRAME_DATA_LENGTH); ++i)
        {
            _IUart.receiveByte(buf[i]);
        }

        return E_OK;
    }

    Std_ReturnType_t UartFrameAepAdapter::setTxBuf(byte_t txData[UART_FRAME_DATA_LENGTH])
    {
        txFrame.data = &txData[0];

        return E_OK;
    }

    Std_ReturnType_t UartFrameAepAdapter::updateHeader(TransportHeader_t& header)
    {
        header.Port = _port;
        header.flag = DEF;
        header.seqN = _seq;
        header.checksum = 0;

        return E_OK;
    }

    Std_ReturnType_t UartFrameAepAdapter::connect()
    {
        _seq = 0;
        return E_OK;
    }
}
