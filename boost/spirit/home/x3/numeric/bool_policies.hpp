/*=============================================================================
    Copyright (c) 2009  Hartmut Kaiser
    Copyright (c) 2014  Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_QI_BOOL_POLICIES_SEP_29_2009_0710AM)
#define SPIRIT_QI_BOOL_POLICIES_SEP_29_2009_0710AM

#if defined(_MSC_VER)
#pragma once
#endif

#include "boost/spirit/home/x3/string/detail/string_parse.hpp"
#include "boost/spirit/home/x3/support/traits/move_to.hpp"

namespace boost { namespace spirit { namespace x3
{
    ///////////////////////////////////////////////////////////////////////////
    //  Default boolean policies
    ///////////////////////////////////////////////////////////////////////////
    template <typename T = bool>
    struct bool_policies
    {
        template <typename Iterator, typename Attribute>
        static bool
        parse_true(Iterator& first, Iterator const& last, Attribute& attr_)
        {
            if (detail::string_parse("true", first, last, unused))
            {
                traits::move_to(T(true), attr_);    // result is true
                return true;
            }
            return false;
        }

        template <typename Iterator, typename Attribute>
        static bool
        parse_false(Iterator& first, Iterator const& last, Attribute& attr_)
        {
            if (detail::string_parse("false", first, last, unused))
            {
                traits::move_to(T(false), attr_);   // result is false
                return true;
            }
            return false;
        }
    };
}}}

#endif
