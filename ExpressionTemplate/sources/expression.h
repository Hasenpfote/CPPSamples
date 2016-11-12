﻿#pragma once
#include <cinttypes>

namespace mymath{

template<typename T>
class scalar;

template<typename E, typename T = void>
struct expression_traits
{
    typename typedef const E& ref_type;
};

template<typename T>
struct expression_traits<scalar<T>, T>
{
    typename typedef scalar<T> ref_type;
};

template<typename L, typename Op, typename R>
class expression final
{
    typename typedef expression_traits<L, typename L::value_type>::ref_type l_ref_type;
    typename typedef expression_traits<R, typename R::value_type>::ref_type r_ref_type;
public:
    using value_type = void;

public:
    expression(l_ref_type l, r_ref_type r)
        : l_(l), r_(r)
    {}

    auto operator [] (std::size_t i) const
    {
        return Op::apply(l_[i], r_[i]);
    }
private:
    l_ref_type l_;
    r_ref_type r_;
};

//
struct op_add final
{
public:
    static std::int8_t apply(std::int8_t l, std::int8_t r){ return evaluate(l, r); }
    static std::int16_t apply(std::int16_t l, std::int16_t r){ return evaluate(l, r); }
    static std::int32_t apply(std::int32_t l, std::int32_t r){ return evaluate(l, r); }
    static float apply(float l, float r){ return evaluate(l, r); }
    static double apply(double l, double r){ return evaluate(l, r); }
    static long double apply(long double l, long double r){ return evaluate(l, r); }
private:
    template<typename T>
    static T evaluate(T lhs, T rhs){ return lhs + rhs; }
};

template<typename L, typename R>
auto operator + (const L& lhs, const R& rhs)
{
    return expression<L, op_add, R>(lhs, rhs);
}

//
struct op_subtract final
{
public:
    static std::int8_t apply(std::int8_t l, std::int8_t r){ return evaluate(l, r); }
    static std::int16_t apply(std::int16_t l, std::int16_t r){ return evaluate(l, r); }
    static std::int32_t apply(std::int32_t l, std::int32_t r){ return evaluate(l, r); }
    static float apply(float l, float r){ return evaluate(l, r); }
    static double apply(double l, double r){ return evaluate(l, r); }
    static long double apply(long double l, long double r){ return evaluate(l, r); }
private:
    template<typename T>
    static T evaluate(T lhs, T rhs) { return lhs - rhs; }
};

template<typename L, typename R>
auto operator - (const L& lhs, const R& rhs)
{
    return expression<L, op_subtract, R>(lhs, rhs);
}

//
struct op_multiply final
{
public:
    static std::int8_t apply(std::int8_t l, std::int8_t r){ return evaluate(l, r); }
    static std::int16_t apply(std::int16_t l, std::int16_t r){ return evaluate(l, r); }
    static std::int32_t apply(std::int32_t l, std::int32_t r){ return evaluate(l, r); }
    static float apply(float l, float r){ return evaluate(l, r); }
    static double apply(double l, double r){ return evaluate(l, r); }
    static long double apply(long double l, long double r){ return evaluate(l, r); }
private:
    template<typename T>
    static T evaluate(T lhs, T rhs){ return lhs * rhs; }
};

template<typename L, typename R, class = typename std::enable_if<std::is_arithmetic<R>::value>::type>
expression<L, op_multiply, scalar<R>> operator * (const L& lhs, const R& rhs)
{
    return expression<L, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

template<typename L, typename R, class = typename std::enable_if<std::is_arithmetic<L>::value>::type>
expression<scalar<L>, op_multiply, R> operator * (const L& lhs, const R& rhs)
{
    return expression<scalar<L>, op_multiply, R>(scalar<L>(lhs), rhs);
}

//
struct op_divide final
{
public:
    static std::int8_t apply(std::int8_t l, std::int8_t r){ return evaluate(l, r); }
    static std::int16_t apply(std::int16_t l, std::int16_t r){ return evaluate(l, r); }
    static std::int32_t apply(std::int32_t l, std::int32_t r){ return evaluate(l, r); }
    static float apply(float l, float r){ return evaluate(l, r); }
    static double apply(double l, double r){ return evaluate(l, r); }
    static long double apply(long double l, long double r){ return evaluate(l, r); }
private:
    template<typename T>
    static T evaluate(T lhs, T rhs) { return lhs / rhs; }
};

template<typename L, typename T>
auto operator / (const L& lhs, const T& rhs)
{
    return expression<L, op_divide, scalar<T>>(lhs, scalar<T>(rhs));
}

//
template<typename T>
class scalar final
{
public:
    using type = scalar<T>;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
    scalar() = default;
    explicit scalar(const_reference value)
        : value_(value)
    {
    }

    value_type operator [] (std::size_t) const { return value_; }
    const_reference value_;
};

}