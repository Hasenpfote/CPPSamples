﻿#pragma once

namespace example{ namespace math{

// Ctor and Dtor.
template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::matrix(const type& other)
{
    storage_ = other.storage_;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::matrix(const storage_type& storage)
{
    storage_ = storage;
}

// Assignment operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator = (const type & other)
{
    storage_ = other.storage_;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator += (const type& other)
{
    for(typename matrix::size_type i = 0; i < size(); i++)
        storage_[i] += other[i];
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator -= (const type& other)
{
    for(typename matrix::size_type i = 0; i < size(); i++)
        storage_[i] -= other[i];
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator *= (value_type scalar)
{
    for(typename matrix::size_type i = 0; i < size(); i++)
        storage_[i] *= scalar;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator /= (value_type divisor)
{
    for(typename matrix::size_type i = 0; i < size(); i++)
        storage_[i] /= divisor;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
template<typename _Order>
typename std::enable_if<std::is_same<_Order, column_major_order>::value, matrix<T, M, N, Order>>::type& matrix<T, M, N, Order>::operator *= (const matrix<T, N, N, Order>& other)
{
    matrix temp(*this);
    typename matrix::value_type elem;
    for(typename matrix::size_type i = 0; i < N; i++){
        for(typename matrix::size_type j = 0; j < M; j++){
            elem = 0;
            for(typename matrix::size_type k = 0; k < N; k++){
                elem += temp(j, k) * other(k, i);
            }
            (*this)(j,i) = elem;
        }
    }
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
template<typename _Order>
typename std::enable_if<std::is_same<_Order, row_major_order>::value, matrix<T, M, N, Order>>::type& matrix<T, M, N, Order>::operator *= (const matrix<T, N, N, Order>& other)
{
    matrix temp(*this);
    typename matrix::value_type elem;
    for(typename matrix::size_type i = 0; i < M; i++){
        for(typename matrix::size_type j = 0; j < N; j++){
            elem = 0;
            for(typename matrix::size_type k = 0; k < N; k++){
                elem += temp(i, k) * other(k, j);
            }
            (*this)(i, j) = elem;
        }
    }
    return *this;
}

// Casting operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::operator pointer ()
{
    return storage_.data();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::operator const_pointer () const
{
    return storage_.data();
}

// Subscript operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::reference matrix<T, M, N, Order>::operator [] (size_type i)
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::value_type matrix<T, M, N, Order>::operator [] (size_type i) const
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::reference matrix<T, M, N, Order>::operator () (size_type row, size_type column)
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::value_type matrix<T, M, N, Order>::operator () (size_type row, size_type column) const
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::rows()
{
    return M;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::columns()
{
    return N;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::size()
{
    return rows() * columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column)
{
    return index(row, column, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index)
{
    return row_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index)
{
    return column_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column, detail::column_major_order_tag)
{
    return column * rows() + row;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column, detail::row_major_order_tag)
{
    return row * columns() + column;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index, detail::column_major_order_tag)
{
    return index % rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index, detail::column_major_order_tag)
{
    return index / rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index, detail::row_major_order_tag)
{
    return index / columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index, detail::row_major_order_tag)
{
    return index % columns();
}

//
template<typename T, std::size_t M, std::size_t N, typename Order>
template<std::size_t _M>
typename std::enable_if<is_square_matrix<_M, N>::value, T>::type matrix<T, M, N, Order>::trace()
{
    typename matrix::value_type result = 0;
    for(typename matrix::size_type i = 0; i < M; i++)
        result += (*this)(i, i);
    return result;
}

// Unary operator.

// Binary operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator + (const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    return matrix<T, M, N, Order>(lhs) += rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator - (const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    return matrix<T, M, N, Order>(lhs) -= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator * (const matrix<T, M, N, Order>& lhs, typename matrix<T, M, N, Order>::value_type rhs)
{
    return matrix<T, M, N, Order>(lhs) *= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator * (typename matrix<T, M, N, Order>::value_type lhs, const matrix<T, M, N, Order>& rhs)
{
    return matrix<T, M, N, Order>(rhs) *= lhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator / (const matrix<T, M, N, Order>& lhs, typename matrix<T, M, N, Order>::value_type rhs)
{
    return matrix<T, M, N, Order>(lhs) /= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order> operator * (const matrix<T, M, N, Order>& lhs, const matrix<T, N, N, Order>& rhs)
{
    return matrix<T, M, N, Order>(lhs) *= rhs;
}

// Stream out.
template<typename T, std::size_t M, std::size_t N, typename Order>
std::ostream& operator << (std::ostream& os, const matrix<T, M, N, Order>& m)
{
    using type = matrix<T, M, N, Order>;
    const auto flags = os.flags();
    for(typename type::size_type i = 0; i < type::rows(); i++){
        os << "matrix(" << i << "){" << m(i, 0);
        for(typename type::size_type j = 1; j < type::columns(); j++){
            os << ", " << m(i, j);
        }
        os << "}" << std::endl;
    }
    os.flags(flags);
    return os;
}

}}