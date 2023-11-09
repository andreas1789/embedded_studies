#include "uartFrame.hpp"

namespace services
{

    Std_ReturnType_t UartFrameAepAdapter::send()
    {
        updateHeader();

        byte_t *buf = reinterpret_cast<byte_t *>(&txFrame);

        for (uint8_t i=0U; i < (sizeof(txFrame.header) + UART_FRAME_DATA_LENGTH); ++i)
        {
            IUart->sendByte(buf[i]);
        }

        return E_OK;
    }

    Std_ReturnType_t UartFrameAepAdapter::receive()
    {

    }

    Std_ReturnType_t UartFrameAepAdapter::setTxBuf(byte_t txData[UART_FRAME_DATA_LENGTH])
    {
        txFrame.data = &txData[0];

        return E_OK;
    }
}
