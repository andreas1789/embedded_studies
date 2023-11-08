#ifndef _TYPES_H_
#define _TYPES_H_

namespace types
{
    typedef unsigned long uint32_t;
    typedef unsigned short uint16_t;
    typedef unsigned char uint8_t;
    typedef long sint32_t;
    typedef short sint16_t;
    typedef char sint8_t;
    typedef char byte_t;

    enum Std_ReturnType_t : uint8_t
    {
        E_OK,
        E_NOT_OK,
    };
}

#endif