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
//
////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <type_traits>

#include "Detail.hPP"
#include "Traits.hpp"

template<class From, class To>
constexpr bool ConvertibleTo = require<
  concepts::Convertible<From, To>
>;

template<class T>
constexpr bool Destructable = require<
  std::is_nothrow_destructible<T>::value
>;

template<class T, class ...Args>
constexpr bool Constructable = require<
  Destructable<T>,
  concepts::Constructable<T, Args...>
>;

template<class T>
constexpr bool DefaultConstructable = require<
  Constructable<T>
>;

template<class T>
constexpr bool MoveConstructable = require<
  Constructable<T, T>,
  ConvertibleTo<T, T>
>;

template<class T>
constexpr bool CopyConstructable = require<
  MoveConstructable<T>,
  Constructable<T, T&>, ConvertibleTo<T&, T>,
  Constructable<T, const T&>, ConvertibleTo<const T&, T>,
  Constructable<T, const T>, ConvertibleTo<const T, T>
>;

template<class T>
constexpr bool Assignable = require<
  concepts::LvalueReference<T>
>;

template<class T>
constexpr bool Copyable = require<
  concepts::CopyAssignable<T>,
  concepts::CopyConstructable<T>
>;

template<class T>
constexpr bool Swappable = require<
  concepts::Swappable<T>
>;

template<class T>
constexpr bool Moveable = require<
  concepts::Object<T>,
  concepts::MoveAssignable<T>,
  concepts::MoveConstructable<T>,
  Swappable<T>
>;

template<class T>
constexpr bool Semiregular = require<
  Copyable<T>,
  concepts::DefaultConstructable<T>
>;

template<class T>
constexpr bool Regular = require<
  Semiregular<T>,
  exists<ops::equal, T, T>
>;

template<class T>
constexpr bool Boolean = require<
  Moveable<T>,
  either<
  concepts::Same<bool, T>,
  concepts::Convertible<T, bool>
  >
>;

template<class T, class U>
constexpr bool WeaklyEqualityComparableWith = require<
  Boolean<ops::equal<traits::remove_reference_t<T>, traits::remove_reference_t<U>>>,
  Boolean<ops::not_equal<traits::remove_reference_t<T>, traits::remove_reference_t<U>>>,
  Boolean<ops::equal<traits::remove_reference_t<U>, traits::remove_reference_t<T>>>,
  Boolean<ops::not_equal<traits::remove_reference_t<U>, traits::remove_reference_t<T>>>
>;

template<class T>
constexpr bool EqualityComparable = require<
  WeaklyEqualityComparableWith<T, T>
>;

template<class T, class U>
constexpr bool EqualityComparableWith = require<
  EqualityComparable<T>,
  EqualityComparable<U>,
  WeaklyEqualityComparableWith<T, U>
>;

template<class T>
constexpr bool WeaklyIncrementable = require<
  Regular<T>,
  exists<ops::prefix_increment, T>
>;

template<class T>
constexpr bool Incrementable = require<
  Regular<T>,
  WeaklyIncrementable<T>,
  exists<ops::postfix_increment, T>
>;

template<class T>
constexpr bool WeaklyDecrementable = require<
  Regular<T>,
  exists<ops::prefix_decrement, T>
>;

template<class T>
constexpr bool Decrementable = require<
  Regular<T>,
  WeaklyDecrementable<T>,
  exists<ops::postfix_decrement, T>
>;

template<class T, class ...Args>
constexpr bool Invocable = require<
  exists<ops::function_call, T, Args...>
>;

template<class T, class ...Args>
constexpr bool Predicate = require<
  Invocable<T, Args...>,
  Boolean<concepts::ResultOfInvoke_t<T, Args...>>
>;

template<class Base, class Derived>
constexpr bool DerivedFrom = require<
  concepts::BaseOf<Base, Derived>,
  concepts::Convertible<Derived, Base>
>;

template<class Base, class Derived>
constexpr bool IsBaseOf = require<
  concepts::BaseOf<Base, Derived>
>;

template<class T>
constexpr bool Integral = require<
  concepts::Integral<T>
>;

template<class T>
constexpr bool SignedIntegral = require<
  Integral<T>,
  concepts::Signed<T>
>;

template<class T>
constexpr bool UnsignedIntegral = require<
  Integral<T>,
  concepts::Unsigned<T>
>;

template<class T>
constexpr bool FloatingPoint = require<
  concepts::FloatingPoint<T>
>;

template<class T>
constexpr bool Readable = require<
  concepts::Same<
  traits::add_lvalue_reference_t<T>,
  ops::dereference<T>
  >
>;

template<class T>
constexpr bool Pointer = require<
  concepts::Pointer<T>
>;

template<class Out, class T>
constexpr bool Writeable = require<
  // ???
>;

template<class T>
constexpr bool Iterator = require<
  exists<ops::dereference, T>,
  WeaklyIncrementable<T>
>;

template<class S, class I>
constexpr bool Sentinel = require<
  Semiregular<S>,
  Iterator<I>,
  WeaklyEqualityComparableWith<S, I>
>;

template<class T>
constexpr bool InputIterator = require<
  Iterator<T>,
  Readable<T>
>;

template<class T>
constexpr bool ForwardIterator = require<
  InputIterator<T>,
  Incrementable<T>,
  Sentinel<T, T>
>;

template<class T>
constexpr bool RandomAccessIterator = require<
  Iterator<T>,
  concepts::Same<
  T,
  ops::binary_plus<T, T>
  >
>;

template<class T>
constexpr bool BidirectionalIterator = require<
  ForwardIterator<T>,
  concepts::Same<T&, ops::prefix_decrement_t<T>>,
  concepts::Same<T&&, ops::postfix_decrement_t<T>>
>;
