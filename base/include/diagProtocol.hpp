#include "types.hpp"
#include "uart.hpp"

using namespace types;

namespace services
{
    enum ServiceIdentifier : uint8_t
    {
        SidSessionControl,
        ReadData,
        WriteData,
        Reset,
    };

    typedef struct 
    {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    } DataParameters;

    enum SessionControl : uint8_t
    {
        Default,
        Programming,
        ReadData,
    };

    typedef struct 
    {
        ServiceIdentifier sid;
        DataParameters dataPrm;
    } DiagMessage;
    
}