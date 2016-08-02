﻿#pragma once
#include <iterator>
#include <type_traits>
#include "detail/range_iterator_base.h"

namespace example{ namespace range{

template <typename T>
class range final
{
    static_assert(std::is_integral<T>::value, "T must be a integer type.");
    static_assert(!std::is_same<T, bool>::value, "bool type is not supported.");

public:
    struct iterator final : public detail::range_iterator_base<T>
    {
    public:
        iterator(T position, T step) : range_iterator_base<T>(position), step(step) {}

        iterator& operator ++ ()
        {
            position += step;
            return *this;
        }

        iterator operator ++ (int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        T step;
    };

public:
    range() = delete;
    ~range() = default;

    range(const range&) = default;
    range& operator = (const range&) = default;
    range(range&&) = default;
    range& operator = (range&&) = default;

    range(const T& first, const T& last)
        : first(first), last(last)
    {
    }

    iterator begin() const
    {
        return iterator(first, (last >= first)? +1 : -1);
    }
    iterator end() const
    {
        return iterator(last, (last >= first) ? +1 : -1);
    }

private:
    T first;
    T last;
};

}}