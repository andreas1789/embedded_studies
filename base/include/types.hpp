#ifndef B83363A8_8F0F_4931_BAD8_649DB872EED7
#define B83363A8_8F0F_4931_BAD8_649DB872EED7
namespace types
{
    typedef unsigned long uint32_t;
    typedef unsigned short uint16_t;
    typedef unsigned char uint8_t;
    typedef long sint32_t;
    typedef short sint16_t;
    typedef char sint8_t;

    template<typename T, uint32_t Capacity>
    class List
    {
        private:
        T _data[Capacity];
        uint32_t _size;

        public:
        List() : _size(0) {}

        void push(const T& value)
        {
            if (_size < Capacity)
            {
                _data[_size] = value;
                ++_size;
            }
        }

        T pop()
        {
            if (_size > 0)
            {
                return _data[_size];
            }
            return 0; // todo
        }
    };
}


#endif /* B83363A8_8F0F_4931_BAD8_649DB872EED7 */
