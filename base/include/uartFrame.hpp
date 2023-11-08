#include "types.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
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
        byte_t data[32];

    } TransportFrame_t;
    
    enum AepState_t : uint8_t
    {
        UNCONNECTED,
        CONNECTED,
    };

    class UartFrameAepAdapter: public ::peripherals::Uart
    {
    public:
        UartFrameAepAdapter(uint8_t port);
        ~UartFrameAepAdapter();

        Std_ReturnType_t connect();
        Std_ReturnType_t disconnect();
        Std_ReturnType_t send();
        Std_ReturnType_t receive();
        Std_ReturnType_t writeTxBuf(byte_t txData[32]);
        Std_ReturnType_t readRxBuf(byte_t rxData[32]);

    private:
        Std_ReturnType_t sendFrame(TransportFrame_t *frame);
        Std_ReturnType_t receiveFrame(TransportFrame_t *frame);

        byte_t sendBuffer[32];
        byte_t receiveBuffer[32];

        AepState_t state;
    };

}