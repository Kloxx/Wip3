#pragma once

#include <cassert>

template <typename T, size_t size_template>
struct Array
{
    typedef size_t size_type;
    typedef T value_type;

    value_type&
    operator[](const size_t& index)
    {
        assert( index < size_template );
        return container[index];
    }

    const value_type&
    operator[](const size_t& index) const
    {
        assert( index < size_template );
        return container[index];
    }

    static
    size_type
    size()
    {
        return size_template;
    }

protected:

    T container[size_template];
};


