//  (C) Copyright John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

//  See boost/type_traits/*.hpp for full copyright notices.

#ifndef BOOST_TYPE_TRAITS_HPP
#define BOOST_TYPE_TRAITS_HPP

#include "prezicsson_boost/type_traits/add_const.hpp"
#include "prezicsson_boost/type_traits/add_cv.hpp"
#include "prezicsson_boost/type_traits/add_lvalue_reference.hpp"
#include "prezicsson_boost/type_traits/add_pointer.hpp"
#include "prezicsson_boost/type_traits/add_reference.hpp"
#include "prezicsson_boost/type_traits/add_rvalue_reference.hpp"
#include "prezicsson_boost/type_traits/add_volatile.hpp"
#include "prezicsson_boost/type_traits/aligned_storage.hpp"
#include "prezicsson_boost/type_traits/alignment_of.hpp"
#include "prezicsson_boost/type_traits/common_type.hpp"
#include "prezicsson_boost/type_traits/conditional.hpp"
#include "prezicsson_boost/type_traits/decay.hpp"
#include "prezicsson_boost/type_traits/extent.hpp"
#include "prezicsson_boost/type_traits/floating_point_promotion.hpp"
#include "prezicsson_boost/type_traits/function_traits.hpp"
#if !defined(__BORLANDC__) && !defined(__CUDACC__)
#include "prezicsson_boost/type_traits/has_new_operator.hpp"
#endif
#include "prezicsson_boost/type_traits/has_nothrow_assign.hpp"
#include "prezicsson_boost/type_traits/has_nothrow_constructor.hpp"
#include "prezicsson_boost/type_traits/has_nothrow_copy.hpp"
#include "prezicsson_boost/type_traits/has_nothrow_destructor.hpp"
#include "prezicsson_boost/type_traits/has_operator.hpp"
#include "prezicsson_boost/type_traits/has_trivial_assign.hpp"
#include "prezicsson_boost/type_traits/has_trivial_constructor.hpp"
#include "prezicsson_boost/type_traits/has_trivial_copy.hpp"
#include "prezicsson_boost/type_traits/has_trivial_destructor.hpp"
#include "prezicsson_boost/type_traits/has_trivial_move_assign.hpp"
#include "prezicsson_boost/type_traits/has_trivial_move_constructor.hpp"
#include "prezicsson_boost/type_traits/has_virtual_destructor.hpp"
#include "prezicsson_boost/type_traits/is_abstract.hpp"
#include "prezicsson_boost/type_traits/is_arithmetic.hpp"
#include "prezicsson_boost/type_traits/is_array.hpp"
#include "prezicsson_boost/type_traits/is_base_and_derived.hpp"
#include "prezicsson_boost/type_traits/is_base_of.hpp"
#include "prezicsson_boost/type_traits/is_class.hpp"
#include "prezicsson_boost/type_traits/is_complex.hpp"
#include "prezicsson_boost/type_traits/is_compound.hpp"
#include "prezicsson_boost/type_traits/is_const.hpp"
#include "prezicsson_boost/type_traits/is_convertible.hpp"
#include "prezicsson_boost/type_traits/is_copy_constructible.hpp"
#include "prezicsson_boost/type_traits/is_copy_assignable.hpp"
#include "prezicsson_boost/type_traits/is_empty.hpp"
#include "prezicsson_boost/type_traits/is_enum.hpp"
#include "prezicsson_boost/type_traits/is_float.hpp"
#include "prezicsson_boost/type_traits/is_floating_point.hpp"
#include "prezicsson_boost/type_traits/is_function.hpp"
#include "prezicsson_boost/type_traits/is_fundamental.hpp"
#include "prezicsson_boost/type_traits/is_integral.hpp"
#include "prezicsson_boost/type_traits/is_lvalue_reference.hpp"
#include "prezicsson_boost/type_traits/is_member_function_pointer.hpp"
#include "prezicsson_boost/type_traits/is_member_object_pointer.hpp"
#include "prezicsson_boost/type_traits/is_member_pointer.hpp"
#include "prezicsson_boost/type_traits/is_nothrow_move_assignable.hpp"
#include "prezicsson_boost/type_traits/is_nothrow_move_constructible.hpp"
#include "prezicsson_boost/type_traits/is_object.hpp"
#include "prezicsson_boost/type_traits/is_pod.hpp"
#include "prezicsson_boost/type_traits/is_polymorphic.hpp"
#include "prezicsson_boost/type_traits/is_pointer.hpp"
#include "prezicsson_boost/type_traits/is_reference.hpp"
#include "prezicsson_boost/type_traits/is_rvalue_reference.hpp"
#include "prezicsson_boost/type_traits/is_signed.hpp"
#include "prezicsson_boost/type_traits/is_same.hpp"
#include "prezicsson_boost/type_traits/is_scalar.hpp"
#include "prezicsson_boost/type_traits/is_stateless.hpp"
#include "prezicsson_boost/type_traits/is_union.hpp"
#include "prezicsson_boost/type_traits/is_unsigned.hpp"
#include "prezicsson_boost/type_traits/is_void.hpp"
#include "prezicsson_boost/type_traits/is_virtual_base_of.hpp"
#include "prezicsson_boost/type_traits/is_volatile.hpp"
#include "prezicsson_boost/type_traits/make_unsigned.hpp"
#include "prezicsson_boost/type_traits/make_signed.hpp"
#include "prezicsson_boost/type_traits/rank.hpp"
#include "prezicsson_boost/type_traits/remove_bounds.hpp"
#include "prezicsson_boost/type_traits/remove_extent.hpp"
#include "prezicsson_boost/type_traits/remove_all_extents.hpp"
#include "prezicsson_boost/type_traits/remove_const.hpp"
#include "prezicsson_boost/type_traits/remove_cv.hpp"
#include "prezicsson_boost/type_traits/remove_pointer.hpp"
#include "prezicsson_boost/type_traits/remove_reference.hpp"
#include "prezicsson_boost/type_traits/remove_volatile.hpp"
#include "prezicsson_boost/type_traits/type_with_alignment.hpp"
#if !(defined(__sgi) && defined(__EDG_VERSION__) && (__EDG_VERSION__ == 238))
#include "prezicsson_boost/type_traits/integral_promotion.hpp"
#include "prezicsson_boost/type_traits/promote.hpp"
#endif

#include "prezicsson_boost/type_traits/ice.hpp"

#endif // BOOST_TYPE_TRAITS_HPP
