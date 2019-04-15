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

#include "Detect.hpp"

namespace concepts
{

  template<class T, class U>
  constexpr bool SwappableWith = exists<detail::swap_with, T, U>;

  template<class T>
  constexpr bool Swappable = SwappableWith<T&, T&>;

  template<class T>
  constexpr bool Pointer = std::is_pointer<T>::value;

  template<class T>
  constexpr bool Integral = std::is_integral<T>::value;

  template<class T>
  constexpr bool FloatingPoint = std::is_floating_point<T>::value;

  template<class T, class U>
  constexpr bool Array = std::is_array<T>::value;

  template<class T>
  constexpr bool Enum = std::is_enum<T>::value;

  template<class T>
  constexpr bool Class = std::is_class<T>::value;

  template<class T, class U>
  constexpr bool Function = std::is_function<T>::value;

  template<class T>
  constexpr bool Union = std::is_union<T>::value;

  template<class T>
  constexpr bool Void = std::is_void<T>::value;

  template<class T>
  constexpr bool Fundamental = std::is_fundamental<T>::value;

  template<class T>
  constexpr bool Arithmetic = std::is_arithmetic<T>::value;

  template<class T>
  constexpr bool Scalar = std::is_scalar<T>::value;

  template<class T>
  constexpr bool Object = std::is_object<T>::value;

  template<class T>
  constexpr bool Compound = std::is_compound<T>::value;

  template<class T>
  constexpr bool LvalueReference = std::is_lvalue_reference<T>::value;

  template<class T>
  constexpr bool RvalueReference = std::is_rvalue_reference<T>::value;

  template<class T>
  constexpr bool MemberPointer = std::is_member_pointer<T>::value;

  template<class T>
  constexpr bool MemberObjectPointer = std::is_member_object_pointer<T>::value;

  template<class T>
  constexpr bool MemberFunctionPointer = std::is_member_function_pointer<T>::value;

  template<class T>
  constexpr bool Reference = std::is_reference<T>::value;

  template<class T>
  constexpr bool Const = std::is_const<T>::value;

  template<class T>
  constexpr bool Volatile = std::is_volatile<T>::value;

  template<class T>
  constexpr bool Trivial = std::is_trivial<T>::value;

  template<class T>
  constexpr bool StandardLayout = std::is_standard_layout<T>::value;

  template<class T, class U>
  constexpr bool LiteralType = std::is_literal_type<T>::value;

  template<class T>
  constexpr bool Empty = std::is_empty<T>::value;

  template<class T>
  constexpr bool Polymorphic = std::is_polymorphic<T>::value;

  template<class T>
  constexpr bool Abstract = std::is_abstract<T>::value;

  template<class T>
  constexpr bool Final = std::is_final<T>::value;

  template<class T>
  constexpr bool Aggregate = std::is_aggregate<T>::value;

  template<class T>
  constexpr bool Signed = std::is_signed<T>::value;

  template<class T>
  constexpr bool Unsigned = std::is_unsigned<T>::value;

  template<class Base, class Derived>
  constexpr bool BaseOf = std::is_base_of<Base, Derived>::value;

  template<class From, class To>
  constexpr bool Convertible = std::is_convertible<From, To>::value;

  template<class T, class ...Args>
  constexpr bool Callable = std::is_invocable<T, Args...>::value;

  template<class T, class ...Args>
  using has_constructor = decltype(T(std::declval<Args>()...));

  template<class T, class ...Args>
  constexpr bool Constructable = exists<has_constructor, T, Args...>;

  template<class T, class ...Args>
  constexpr bool TriviallyConstructable = std::is_trivially_constructible<T, Args...>::value;

  template<class T, class ...Args>
  constexpr bool NothrowConstructable = std::is_nothrow_constructible<T, Args...>::value;

  template<class T>
  constexpr bool DefaultConstructable = std::is_default_constructible<T>::value;

  template<class T>
  constexpr bool VirtualDestructor = std::has_virtual_destructor<T>::value;

  template<class T>
  constexpr bool CopyConstructable = std::is_copy_constructible<T>::value;

  template<class T>
  constexpr bool MoveConstructable = std::is_move_constructible<T>::value;

  template<class T>
  using copy_assignable = decltype(std::declval<T&>() = std::declval<const T&>());

  template<class T>
  constexpr bool CopyAssignable = identical_to<T&, copy_assignable, T>;

  template<class T>
  using move_assignable = decltype(std::declval<T&>() = std::declval<T&&>());

  template<class T>
  constexpr bool MoveAssignable = identical_to<T&, move_assignable, T>;

  template<class T, class U>
  constexpr bool AssignableFrom = exists<ops::assignment, T, U>;

  template<class T, class U>
  constexpr bool Same = std::is_same<T, U>::value;

  template<class F, class ...Args>
  using ResultOfInvoke_t = std::invoke_result_t<F, Args...>;

  template<class Base, class Derived>
  constexpr bool IsBase = std::is_base_of<Base, Derived>::value;

  template<class ...T>
  using CommonType = std::common_type<T...>;

  template<class ...T>
  using CommonReference = CommonType<T...>;

}
