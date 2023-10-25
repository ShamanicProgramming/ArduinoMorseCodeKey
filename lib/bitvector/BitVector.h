#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include <Arduino.h>
#include "fill.h"

/*
Bitvector modified from https://stackoverflow.com/a/8566412
*/

class BitVectorBase
{
protected:
    class bitref
    { // Prevent this class from being used anywhere else.
    public:
        bitref(uint32_t &an_int, uint32_t mask)
            : an_int_(an_int), mask_(mask)
        {
        }

        const bitref &operator=(bool val)
        {
            if (val)
            {
                an_int_ |= mask_;
            }
            else
            {
                an_int_ &= ~mask_;
            }
            return *this;
        }
        const bitref &operator=(const bitref &br)
        {
            return this->operator=(bool(br));
        }
        operator bool() const
        {
            return ((an_int_ & mask_) != 0) ? true : false;
        }

    private:
        uint32_t &an_int_;
        uint32_t mask_;
    };
};

template <size_t Size>
class BitVector : public BitVectorBase
{
private:
    static constexpr size_t numints = ((Size + 31) / 32);

public:
    BitVector() { fill(ints_, ints_ + numints, 0); }

    bool operator[](size_t bitnum) const
    {
        const size_t bytenum = bitnum / 32;
        bitnum = bitnum % 32;
        return ((ints_[bytenum] & (uint32_t(1) << bitnum)) != 0) ? true : false;
    }
    bitref operator[](size_t bitnum)
    {
        const size_t bytenum = bitnum / 32;
        bitnum = bitnum % 32;
        uint32_t mask = uint32_t(1) << bitnum;
        return bitref(ints_[bytenum], mask);
    }

private:
    uint32_t ints_[numints];
};
#endif