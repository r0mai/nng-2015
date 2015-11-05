
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED
#define BOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED

#include "prezicsson_boost//config.hpp"
#include "prezicsson_boost//type_traits/has_trivial_move_assign.hpp"
#include "prezicsson_boost//type_traits/has_nothrow_assign.hpp"
#include "prezicsson_boost//type_traits/is_array.hpp"
#include "prezicsson_boost//type_traits/is_reference.hpp"
#include "prezicsson_boost//type_traits/detail/ice_and.hpp"
#include "prezicsson_boost//type_traits/detail/ice_or.hpp"
#include "prezicsson_boost//type_traits/detail/ice_not.hpp"
#include "prezicsson_boost//utility/enable_if.hpp"
#include "prezicsson_boost//utility/declval.hpp"

// should be the last #include
#include "prezicsson_boost//type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail{

#ifdef BOOST_IS_NOTHROW_MOVE_ASSIGN

template <class T>
struct is_nothrow_move_assignable_imp{ BOOST_STATIC_CONSTANT(bool, value = BOOST_IS_NOTHROW_MOVE_ASSIGN(T)); };
template <class T>
struct is_nothrow_move_assignable_imp<T const>{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <class T>
struct is_nothrow_move_assignable_imp<T volatile>{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <class T>
struct is_nothrow_move_assignable_imp<T const volatile>{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <class T>
struct is_nothrow_move_assignable_imp<T&>{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <class T>
struct is_nothrow_move_assignable_imp<T&&>{ BOOST_STATIC_CONSTANT(bool, value = false); };


#elif !defined(BOOST_NO_CXX11_NOEXCEPT) && !defined(BOOST_NO_SFINAE_EXPR)

template <class T, class Enable = void>
struct false_or_cpp11_noexcept_move_assignable: public ::boost::false_type {};

template <class T>
struct false_or_cpp11_noexcept_move_assignable <
        T,
        typename ::boost::enable_if_c<sizeof(T) && BOOST_NOEXCEPT_EXPR(::boost::declval<T&>() = ::boost::declval<T>())>::type
    > : public ::boost::integral_constant<bool, BOOST_NOEXCEPT_EXPR(::boost::declval<T&>() = ::boost::declval<T>())>
{};

template <class T>
struct is_nothrow_move_assignable_imp{
    BOOST_STATIC_CONSTANT(bool, value = ::boost::detail::false_or_cpp11_noexcept_move_assignable<T>::value);
};

template <class T>
struct is_nothrow_move_assignable_imp<T const> : public ::boost::false_type {};
template <class T>
struct is_nothrow_move_assignable_imp<T volatile> : public ::boost::false_type{};
template <class T>
struct is_nothrow_move_assignable_imp<T const volatile> : public ::boost::false_type{};
template <class T>
struct is_nothrow_move_assignable_imp<T&> : public ::boost::false_type{};
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class T>
struct is_nothrow_move_assignable_imp<T&&> : public ::boost::false_type{};
#endif

#else

template <class T>
struct is_nothrow_move_assignable_imp{
    BOOST_STATIC_CONSTANT(bool, value = (
        ::boost::type_traits::ice_and<
            ::boost::type_traits::ice_or<
                ::boost::has_trivial_move_assign<T>::value,
                ::boost::has_nothrow_assign<T>::value
            >::value,
            ::boost::type_traits::ice_not< ::boost::is_array<T>::value >::value
        >::value));
};

#endif

}

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_nothrow_move_assignable,T,::boost::detail::is_nothrow_move_assignable_imp<T>::value)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_assignable,void,false)
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_assignable,void const,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_assignable,void const volatile,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_assignable,void volatile,false)
#endif

} // namespace boost

#include "prezicsson_boost//type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED