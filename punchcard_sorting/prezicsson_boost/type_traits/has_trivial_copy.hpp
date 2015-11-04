
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_HAS_TRIVIAL_COPY_HPP_INCLUDED
#define BOOST_TT_HAS_TRIVIAL_COPY_HPP_INCLUDED

#include "prezicsson_boost/type_traits/config.hpp"
#include "prezicsson_boost/type_traits/intrinsics.hpp"
#include "prezicsson_boost/type_traits/is_volatile.hpp"
#include "prezicsson_boost/type_traits/is_pod.hpp"
#include "prezicsson_boost/type_traits/detail/ice_and.hpp"
#include "prezicsson_boost/type_traits/detail/ice_or.hpp"
#include "prezicsson_boost/type_traits/detail/ice_not.hpp"

#ifdef __clang__
#include "prezicsson_boost/type_traits/is_copy_constructible.hpp"
#endif

// should be the last #include
#include "prezicsson_boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail {

template <typename T>
struct has_trivial_copy_impl
{
#ifdef BOOST_HAS_TRIVIAL_COPY
#  ifdef __clang__
   BOOST_STATIC_CONSTANT(bool, value = BOOST_HAS_TRIVIAL_COPY(T) && boost::is_copy_constructible<T>::value);
#  else
   BOOST_STATIC_CONSTANT(bool, value = BOOST_HAS_TRIVIAL_COPY(T));
#  endif
#else
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::is_pod<T>::value,
         ::boost::type_traits::ice_not< ::boost::is_volatile<T>::value >::value
      >::value));
#endif
};

#ifdef __clang__

template <typename T, std::size_t N>
struct has_trivial_copy_impl<T[N]>
{
   static const bool value = has_trivial_copy_impl<T>::value;
};

#endif

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF1(has_trivial_copy,T,::boost::detail::has_trivial_copy_impl<T>::value)
BOOST_TT_AUX_BOOL_TRAIT_DEF1(has_trivial_copy_constructor,T,::boost::detail::has_trivial_copy_impl<T>::value)

BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy,void,false)
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy,void const,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy,void const volatile,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy,void volatile,false)
#endif

BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy_constructor,void,false)
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy_constructor,void const,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy_constructor,void const volatile,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(has_trivial_copy_constructor,void volatile,false)
#endif

} // namespace boost

#include "prezicsson_boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_HAS_TRIVIAL_COPY_HPP_INCLUDED
