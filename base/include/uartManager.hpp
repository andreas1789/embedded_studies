#ifndef BB9695C9_9D6B_4583_8E64_0A2E6EF0C8E3
#define BB9695C9_9D6B_4583_8E64_0A2E6EF0C8E3
#include "types.hpp"
#include "uart.hpp"
#include "uartConsole.hpp"
#include "uartDiagnosis.hpp"

using namespace types;

namespace services
{
    enum class UartStates : uint8_t
    {
        kUartOff = 0x0,
        kUartConsole = 0x1,
        kUartDiagOpen = 0x2,
        kUartDiagData = 0x3,
    };

    enum class UartSessionControl : uint8_t
    {
        kConsole = 0x1,
        kDiag = 0x2,
    };
    
    class UartManager
    {
        public:
        UartManager();
        ~UartManager();

        void run();

        private:
        ::services::UartConsole fUartConsole_;
        ::services::UartDiagnosis fUartDiagnosis_;


        UartStates state_;
    };
}


#endif /* BB9695C9_9D6B_4583_8E64_0A2E6EF0C8E3 */
