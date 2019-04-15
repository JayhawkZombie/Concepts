#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2019 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//`
////////////////////////////////////////////////////////////

#include <algorithm>
#include <utility>
#include <type_traits>

namespace detail
{

  template<class Default, class AlwaysVoid, template<class ...> class Op, class ...Args>
  struct detector
  {
    using value_t = std::false_type;
    using type = Default;
  };

  template<class Default, template<class ...> class Op, class ...Args>
  struct detector<Default, std::void_t<Op<Args...>>, Op, Args...>
  {
    using value_t = std::true_type;
    using type = Op<Args...>;
  };

}

struct nonesuch
{
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(const nonesuch&) = delete;
  void operator =(const nonesuch&) = delete;
};

template<template<class ...> class Op, class ...Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template<template<class ...> class Op, class ...Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template<class Default, template<class ...> class Op, class ...Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

template<class Expected, template<class ...> class Op, class ...Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template<class To, template<class ...> class Op, class ...Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template<bool ...Bs>
constexpr bool require = std::conjunction<std::bool_constant<Bs> ...>::value;

template<bool ...Bs>
constexpr bool either = std::disjunction<std::bool_constant<Bs> ...>::value;

template<bool...Bs>
constexpr bool disallow = !require<Bs...>;

template<template<class ...> class Op, class ...Args>
constexpr bool exists = is_detected<Op, Args...>::value;

template<class To, template<class ...> class Op, class ...Args>
constexpr bool converts_to = is_detected_convertible<To, Op, Args...>::value;

template<class Exact, template<class ...> class Op, class ...Args>
constexpr bool identical_to = is_detected_exact<Exact, Op, Args...>::value;

namespace detail
{
  template<class T, class U = T>
  using swap_with = decltype(std::swap(std::declval<T>(), std::declval<U>()));
}

namespace ops
{
  template<class T>
  using prefix_increment = decltype(++std::declval<T>());

  template<class T>
  using prefix_decrement = decltype(--std::declval<T>());

  template<class T>
  using dereference = decltype(*std::declval<T>());

  template<class T>
  using postfix_increment = decltype(std::declval<T>()++);

  template<class T>
  using postfix_decrement = decltype(std::declval<T>()--);

  template<class T>
  using arrow = decltype(std::declval<T>().operator->());

  template<class T, typename Idx>
  using subscript = decltype(std::declval<T>()[std::declval<Idx>()]);

  template<class T>
  using address_of = decltype(std::declval<T>().operator&());

  template<class T>
  using unary_plus = decltype(+std::declval<T>());

  template<class T>
  using unary_minus = decltype(-std::declval<T>());

  template<class T, class U>
  using binary_plus = decltype(std::declval<const T&>() + std::declval<const U&>());

  template<class T, class U>
  using binary_minus = decltype(std::declval<const T&>() - std::declval<const U&>());

  template<class T, class U>
  using binary_mult = decltype(std::declval<const T&>()* std::declval<const U&>());

  template<class T, class U>
  using binary_div = decltype(std::declval<const T&>() / std::declval<const U&>());

  template<class T, class U>
  using binary_mod = decltype(std::declval<const T&>() % std::declval<const U&>());

  template<class T>
  using bitwise_not = decltype(~std::declval<T&>());

  template<class T, class U>
  using bitwise_and = decltype(std::declval<T&>()& std::declval<T&>());

  template<class T, class U>
  using bitwise_or = decltype(std::declval<T&>() | std::declval<U&>());

  template<class T, class U>
  using bitwise_xor = decltype(std::declval<T&>() ^ std::declval<U&>());

  template<class T, class U>
  using bitwise_shl = decltype(std::declval<T&>() << std::declval<U&>());

  template<class T, class U>
  using bitwise_shr = decltype(std::declval<T&>() >> std::declval<U&>());

  template<class T>
  using logical_not = decltype(!std::declval<T>());

  template<class T, class U>
  using logical_and = decltype(std::declval<T&>() && std::declval<U&>());

  template<class T, class U>
  using logical_or = decltype(std::declval<T&>() || std::declval<U&>());

  template<class T, class U>
  using equal = decltype(std::declval<T>() == std::declval<U>());

  template<class T, class U>
  using not_equal = decltype(std::declval<T>() != std::declval<U>());

  template<class T, class U>
  using less_than = decltype(std::declval<T>() < std::declval<U>());

  template<class T, class U>
  using greater_than = decltype(std::declval<T>() > std::declval<U>());

  template<class T, class U>
  using less_equal = decltype(std::declval<T>() <= std::declval<U>());

  template<class T, class U>
  using greater_equal = decltype(std::declval<T>() >= std::declval<U>());

  template<class T, class U>
  using assignment = decltype(std::declval<T>().operator=(std::declval<const U&>()));

  template<class T>
  using copy_assign = decltype(std::declval<T&>().operator=(std::declval<const T&>()));

  template<class T>
  using move_assign = decltype(std::declval<T&>().operator=(std::declval<T&&>()));

  template<class T>
  using addition_assign = decltype(std::declval<T&>().operator +=(std::declval<const T&>()));

  template<class T>
  using subtract_assign = decltype(std::declval<T&>().operator -=(std::declval<const T&>()));

  template<class T>
  using mult_assign = decltype(std::declval<T&>().operator *=(std::declval<const T&>()));

  template<class T>
  using div_assign = decltype(std::declval<T&>().operator /=(std::declval<const T&>()));

  template<class T>
  using modulo_assign = decltype(std::declval<T&>().operator %=(std::declval<const T&>()));

  template<class T>
  using bitwise_and_assign = decltype(std::declval<T&>().operator &=(std::declval<const T&>()));

  template<class T>
  using bitwise_or_assign = decltype(std::declval<T&>().operator |=(std::declval<const T&>()));

  template<class T>
  using bitwise_xor_assign = decltype(std::declval<T&>().operator ^=(std::declval<const T&>()));

  template<class T>
  using bitwise_shl_assign = decltype(std::declval<T&>().operator <<=(std::declval<const T&>()));

  template<class T>
  using bitwise_shr_assign = decltype(std::declval<T&>().operator >>=(std::declval<const T&>()));

  template<class T, class ...Args>
  using function_call = decltype(std::declval<T&>().operator()(std::declval<Args>()...));

  template<class T, class To>
  using conversion = decltype(std::declval<T&>().operator To());

  template<class T>
  using comma = decltype(std::declval<T&>().operator,(std::declval<T&>()));

}