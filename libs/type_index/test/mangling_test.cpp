// Tests that the non-RTTI emulation of type_info mangling is
// as if RTTI were available
//
// Copyright Niall Douglas 2013.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_index/template_info.hpp>
#include <typeinfo>

#define BOOST_TEST_MODULE mangling_emulation_correct_test_module
#include <boost/test/unit_test.hpp>

template<class T> const char *test()
{
    return __FUNCDNAME__;
}
template<class T> inline void is_mangling_equal()
{
    const boost::template_info &myinfo=boost::template_id<T>();
    const std::type_info &theirinfo=typeid(T);
    const char *mine=myinfo.name();
    const char *theirs=
#ifdef _MSC_VER
      theirinfo.raw_name();
#else
      theirinfo.name();
#endif
    const char *other=test<T>();
    BOOST_CHECK_EQUAL(mine, theirs);
    BOOST_CHECK_EQUAL(other, theirs);
}

template<class T> struct template_type {};
template<template<class> class T> struct template_template_type {};

BOOST_AUTO_TEST_CASE(mangling_emulation_correct)
{
    is_mangling_equal<int>();
    is_mangling_equal<template_type<int>>();
    is_mangling_equal<template_template_type<template_type>>();
}
