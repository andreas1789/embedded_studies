#include "types.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    #define UART_FRAME_DATA_LENGTH 32

    enum TransportFlag_t : uint8_t
    {
        DEF = 0x0,
        SYN = 0x1,
        ACK = 0x2,
        FIN = 0x4,
    };

    typedef struct
    {
        uint8_t Port;
        TransportFlag_t flag;
        uint8_t seqN;
        uint8_t ackN;
        uint8_t checksum;

    } TransportHeader_t;

    typedef struct
    {
        TransportHeader_t header;
        byte_t *data;

    } TransportFrame_t;

    enum AepState_t : uint8_t
    {
        UNCONNECTED,
        CONNECTED,
    };

    class UartFrameAepAdapter
    {
    public:
        UartFrameAepAdapter(uint8_t port, ::peripherals::Uart &iUart);
        ~UartFrameAepAdapter();

        Std_ReturnType_t connect();
        Std_ReturnType_t disconnect();
        Std_ReturnType_t send();
        Std_ReturnType_t receive();
        Std_ReturnType_t setTxBuf(byte_t txData[UART_FRAME_DATA_LENGTH]);
        Std_ReturnType_t setRxBuf(byte_t rxData[UART_FRAME_DATA_LENGTH]);

    private:
        TransportFrame_t txFrame;
        TransportFrame_t rxFrame;

        ::peripherals::Uart *IUart;

        AepState_t _state;
    };

}