#include "uartFrame.hpp"

namespace services
{

    Std_ReturnType_t UartFrameAepAdapter::sendFrame(TransportFrame_t *frame)
    {
        byte_t *buf = reinterpret_cast<byte_t *>(frame);

        for (uint8_t i=0U; i < sizeof(TransportFrame_t); ++i)
        {
            sendByte(buf[i]);
        }

        return E_OK;
    }

}