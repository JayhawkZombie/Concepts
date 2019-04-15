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

#include <type_traits>
#include <iterator>

namespace iterator
{

  template<class Iter>
  using difference_type_t = typename std::iterator_traits<Iter>::difference_type;

  template<class Iter>
  using value_type_t = typename std::iterator_traits<Iter>::value_type;

  template<class Iter>
  using pointer_t = typename std::iterator_traits<Iter>::pointer;

  template<class Iter>
  using reference_t = typename std::iterator_traits<Iter>::reference;

}

namespace traits
{

  template<bool B, class T, class F> struct conditional { using type = T; };
  template<class T, class F>         struct conditional<false, T, F> { using type = F; };
  template<bool B, class T, class F> using conditional_t = typename conditional<B, T, F>::type;

  template<class T> struct type_identity { using type = T; };

  template<class T> using underlying_type_t = typename std::underlying_type<T>::type;

  template<class ...T> using common_type = std::common_type<T...>;
  template<class ...T> using common_type_t = typename std::common_type<T...>::type;

  template<class T> struct add_const { using type = const T; };
  template<class T> using  add_const_t = typename add_const<T>::type;

  template<class T> struct add_volatile { using type = volatile T; };
  template<class T> using  add_volatile_t = typename add_volatile<T>::type;

  template<class T> struct add_const_volatile { using type = const volatile T; };
  template<class T> using  add_const_volatile_t = typename add_const_volatile<T>::type;

  template<class T> struct remove_const { using type = T; };
  template<class T> struct remove_const<const T> { using type = T; };
  template<class T> using  remove_const_t = typename remove_const<T>::type;

  template<class T> struct remove_volatile { using type = T; };
  template<class T> struct remove_volatile<volatile T> { using type = T; };
  template<class T> using  remove_volatile_t = typename remove_volatile<T>::type;
  template<class T> struct remove_const_volatile { using type = typename remove_volatile<typename remove_const<T>::type>::type; };
  template<class T> using  remove_const_volatile_t = typename remove_const_volatile<T>::type;

  template<class T> struct remove_reference { using type = T; };
  template<class T> struct remove_reference<T&> { using type = T; };
  template<class T> struct remove_reference<T&&> { using type = T; };
  template<class T> using  remove_reference_t = typename remove_reference<T>::type;

  template<class T> struct add_lvalue_reference;

  namespace detail
  {
    template<class T> auto try_add_lvalue_reference(int)->type_identity<T&>;
    template<class T> auto try_add_lvalue_reference(...)->type_identity<T>;

    template<class T> auto try_add_rvalue_reference(int)->type_identity<T&&>;
    template<class T> auto try_add_rvalue_reference(...)->type_identity<T>;
  }

  template<class T> struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) { };
  template<class T> struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) { };

  template<class T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
  template<class T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

  template<class T> struct remove_pointer { using type = T; };
  template<class T> struct remove_pointer<T*> { using type = T; };
  template<class T> struct remove_pointer<T* const> { using type = T; };
  template<class T> struct remove_pointer<T* volatile> { using type = T; };
  template<class T> struct remove_pointer<T* const volatile> { using type = T; };
  template<class T> using  remove_pointer_t = typename remove_pointer<T>::type;

  template<class T> struct add_pointer;

  namespace detail
  {
    template<class T> auto try_add_pointer(int)->type_identity<typename remove_reference<T>::type*>;
    template<class T> auto try_add_pointer(...)->type_identity<T>;
  }

  template<class T> struct add_pointer : decltype(detail::try_add_pointer<T>(0)) { };
  template<class T> using  add_pointer_t = typename add_pointer<T>::type;

  template<class T> struct                remove_extent;
  template<class T> struct                remove_extent { using type = T; };
  template<class T> struct                remove_extent<T[]> { using type = T; };
  template<class T, std::size_t N> struct remove_extent<T[N]> { using type = T; };
  template<class T> using                 remove_extent_t = typename remove_extent<T>::type;


  template<class T> struct                remove_all_extents;
  template<class T> struct                remove_all_extents { using type = T; };
  template<class T> struct                remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };
  template<class T, std::size_t N> struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };
  template<class T> using                 remove_all_extents_t = typename remove_all_extents<T>::type;

  template<class T> using  make_signed   = std::make_signed<T>;
  template<class T> using  make_signed_t = typename make_signed<T>::type;

  template<class T> using  make_unsigned   = std::make_unsigned<T>;
  template<class T> using  make_unsigned_t = typename make_unsigned<T>::type;

  template<class T> struct remove_cvref { using type = remove_const_volatile_t<remove_reference_t<T>>; };

  template<class T> struct decay;

  template<class T>
  struct decay
  {
  private:
    using U = typename remove_reference<T>::type;

  public:
    using type = typename conditional<
      std::is_array<U>::value,
      typename remove_extent<U>::type*,
      typename conditional<
      std::is_function<U>::value,
      typename add_pointer<U>::type,
      typename remove_const_volatile<U>::type
      >::type
    >::type;
  };

  template<class T>
  using decay_t = typename decay<T>::type;

}
