#pragma once

#include <cassert>

template <typename T, unsigned int size>
struct Array
{
    typedef size_t size_type;
    typedef T value_type;

    value_type&
    operator[](const size_t& index)
    {
        assert( index < size );
        return container[index];
    }

    value_type
    operator[](const size_t& index) const
    {
        assert( index < size );
        return container[index];
    }

protected:

    T container[size];
};


