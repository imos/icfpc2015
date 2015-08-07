//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Pablo Halpern 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP
#define BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

#include "boost/container/detail/config_begin.hpp"
#include "boost/container/detail/workaround.hpp"
#include "boost/container/container_fwd.hpp"
#include "boost/intrusive/pointer_traits.hpp"
#include "boost/intrusive/detail/memory_util.hpp"
#include "boost/container/detail/memory_util.hpp"
#include "boost/container/detail/mpl.hpp"
#include "boost/container/detail/placement_new.hpp"
#include "boost/move/utility_core.hpp"

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include "boost/container/detail/preprocessor.hpp"
#endif



namespace boost {
namespace container {
namespace allocator_traits_detail {

}

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace container_detail {

//workaround needed for C++03 compilers with no construct()
//supporting rvalue references
template<class A>
struct is_std_allocator
{  static const bool value = false; };

template<class T>
struct is_std_allocator< std::allocator<T> >
{  static const bool value = true; };

}  //namespace container_detail {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! The class template allocator_traits supplies a uniform interface to all allocator types.
//! This class is a C++03-compatible implementation of std::allocator_traits
template <typename Alloc>
struct allocator_traits
{
   //allocator_type
   typedef Alloc allocator_type;
   //value_type
   typedef typename Alloc::value_type         value_type;

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      //! Alloc::pointer if such a type exists; otherwise, value_type*
      //!
      typedef unspecified pointer;
      //! Alloc::const_pointer if such a type exists ; otherwise, pointer_traits<pointer>::rebind<const
      //!
      typedef see_documentation const_pointer;
      //! Non-standard extension
      //! Alloc::reference if such a type exists; otherwise, value_type&
      typedef see_documentation reference;
      //! Non-standard extension
      //! Alloc::const_reference if such a type exists ; otherwise, const value_type&
      typedef see_documentation const_reference;
      //! Alloc::void_pointer if such a type exists ; otherwise, pointer_traits<pointer>::rebind<void>.
      //!
      typedef see_documentation void_pointer;
      //! Alloc::const_void_pointer if such a type exists ; otherwis e, pointer_traits<pointer>::rebind<const
      //!
      typedef see_documentation const_void_pointer;
      //! Alloc::difference_type if such a type exists ; otherwise, pointer_traits<pointer>::difference_type.
      //!
      typedef see_documentation difference_type;
      //! Alloc::size_type if such a type exists ; otherwise, make_unsigned<difference_type>::type
      //!
      typedef see_documentation size_type;
      //! Alloc::propagate_on_container_copy_assignment if such a type exists, otherwise an integral_constant
      //! type with internal constant static member <code>value</code> == false.
      typedef see_documentation propagate_on_container_copy_assignment;
      //! Alloc::propagate_on_container_move_assignment if such a type exists, otherwise an integral_constant
      //! type with internal constant static member <code>value</code> == false.
      typedef see_documentation propagate_on_container_move_assignment;
      //! Alloc::propagate_on_container_swap if such a type exists, otherwise an integral_constant
      //! type with internal constant static member <code>value</code> == false.
      typedef see_documentation propagate_on_container_swap;
      //! Defines an allocator: Alloc::rebind<T>::other if such a type exists; otherwise, Alloc<T, Args>
      //! if Alloc is a class template instantiation of the form Alloc<U, Args>, where Args is zero or
      //! more type arguments ; otherwise, the instantiation of rebind_alloc is ill-formed.
      //!
      //! In C++03 compilers <code>rebind_alloc</code> is a struct derived from an allocator
      //! deduced by previously detailed rules.
      template <class T> using rebind_alloc = see_documentation;

      //! In C++03 compilers <code>rebind_traits</code> is a struct derived from
      //! <code>allocator_traits<OtherAlloc></code>, where <code>OtherAlloc</code> is
      //! the allocator deduced by rules explained in <code>rebind_alloc</code>.
      template <class T> using rebind_traits = allocator_traits<rebind_alloc<T> >;

      //! Non-standard extension: Portable allocator rebind for C++03 and C++11 compilers.
      //! <code>type</code> is an allocator related to Alloc deduced deduced by rules explained in <code>rebind_alloc</code>.
      template <class T>
      struct portable_rebind_alloc
      {  typedef see_documentation type;  };
   #else
      //pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         pointer, value_type*)
            pointer;
      //const_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::container_detail::, Alloc,
         const_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<const value_type>)
               const_pointer;
      //reference
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         reference, typename container_detail::unvoid<value_type>::type&)
            reference;
      //const_reference
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         const_reference, const typename container_detail::unvoid<value_type>::type&)
               const_reference;
      //void_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::container_detail::, Alloc,
         void_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<void>)
               void_pointer;
      //const_void_pointer
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(boost::container::container_detail::, Alloc,
         const_void_pointer, typename boost::intrusive::pointer_traits<pointer>::template
            rebind_pointer<const void>)
               const_void_pointer;
      //difference_type
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         difference_type, std::ptrdiff_t)
            difference_type;
      //size_type
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         size_type, std::size_t)
            size_type;
      //propagate_on_container_copy_assignment
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         propagate_on_container_copy_assignment, container_detail::false_type)
            propagate_on_container_copy_assignment;
      //propagate_on_container_move_assignment
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         propagate_on_container_move_assignment, container_detail::false_type)
            propagate_on_container_move_assignment;
      //propagate_on_container_swap
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(boost::container::container_detail::, Alloc,
         propagate_on_container_swap, container_detail::false_type)
            propagate_on_container_swap;

      #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         //C++11
         template <typename T> using rebind_alloc  = typename boost::intrusive::pointer_rebind<Alloc, T>::type;
         template <typename T> using rebind_traits = allocator_traits< rebind_alloc<T> >;
      #else    // #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         //Some workaround for C++03 or C++11 compilers with no template aliases
         template <typename T>
         struct rebind_alloc : boost::intrusive::pointer_rebind<Alloc,T>::type
         {
            typedef typename boost::intrusive::pointer_rebind<Alloc,T>::type Base;
            #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
            template <typename... Args>
            rebind_alloc(BOOST_FWD_REF(Args)... args)
               : Base(boost::forward<Args>(args)...)
            {}
            #else    // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
            #define BOOST_PP_LOCAL_MACRO(n)                                                        \
            BOOST_PP_EXPR_IF(n, template<) BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_EXPR_IF(n, >) \
            rebind_alloc(BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_LIST, _))                       \
               : Base(BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _))                       \
            {}                                                                                     \
            //
            #define BOOST_PP_LOCAL_LIMITS (0, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
            #include BOOST_PP_LOCAL_ITERATE()
            #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
         };

         template <typename T>
         struct rebind_traits
            : allocator_traits<typename boost::intrusive::pointer_rebind<Alloc, T>::type>
         {};
      #endif   // #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
      template <class T>
      struct portable_rebind_alloc
      {  typedef typename boost::intrusive::pointer_rebind<Alloc, T>::type type;  };
   #endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

   //! <b>Returns</b>: <code>a.allocate(n)</code>
   //!
   static pointer allocate(Alloc &a, size_type n)
   {  return a.allocate(n);  }

   //! <b>Returns</b>: <code>a.deallocate(p, n)</code>
   //!
   //! <b>Throws</b>: Nothing
   static void deallocate(Alloc &a, pointer p, size_type n)
   {  a.deallocate(p, n);  }

   //! <b>Effects</b>: calls <code>a.allocate(n, p)</code> if that call is well-formed;
   //! otherwise, invokes <code>a.allocate(n)</code>
   static pointer allocate(Alloc &a, size_type n, const_void_pointer p)
   {
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_allocate
            <Alloc, const size_type, const const_void_pointer>::value;
      container_detail::bool_<value> flag;
      return allocator_traits::priv_allocate(flag, a, n, p);
   }

   //! <b>Effects</b>: calls <code>a.destroy(p)</code> if that call is well-formed;
   //! otherwise, invokes <code>p->~T()</code>.
   template<class T>
   static void destroy(Alloc &a, T*p) BOOST_CONTAINER_NOEXCEPT
   {
      typedef T* destroy_pointer;
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_destroy
            <Alloc, const destroy_pointer>::value;
      container_detail::bool_<value> flag;
      allocator_traits::priv_destroy(flag, a, p);
   }

   //! <b>Returns</b>: <code>a.max_size()</code> if that expression is well-formed; otherwise,
   //! <code>numeric_limits<size_type>::max()</code>.
   static size_type max_size(const Alloc &a) BOOST_CONTAINER_NOEXCEPT
   {
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_max_size
            <const Alloc>::value;
      container_detail::bool_<value> flag;
      return allocator_traits::priv_max_size(flag, a);
   }

   //! <b>Returns</b>: <code>a.select_on_container_copy_construction()</code> if that expression is well-formed;
   //! otherwise, a.
   static
   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   typename container_detail::if_c
      <  boost::container::container_detail::
                  has_member_function_callable_with_select_on_container_copy_construction
                     <const Alloc>::value
      , Alloc
      , const Alloc &
      >::type
   #else
   Alloc
   #endif
   select_on_container_copy_construction(const Alloc &a)
   {
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_select_on_container_copy_construction
            <const Alloc>::value;
      container_detail::bool_<value> flag;
      return allocator_traits::priv_select_on_container_copy_construction(flag, a);
   }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      //! <b>Effects</b>: calls <code>a.construct(p, std::forward<Args>(args)...)</code> if that call is well-formed;
      //! otherwise, invokes <code>::new (static_cast<void*>(p)) T(std::forward<Args>(args)...)</code>
      template <class T, class ...Args>
      static void construct(Alloc & a, T* p, BOOST_FWD_REF(Args)... args)
      {
         container_detail::bool_<container_detail::is_std_allocator<Alloc>::value> flag;
         allocator_traits::priv_construct(flag, a, p, ::boost::forward<Args>(args)...);
      }
   #endif
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      private:
      static pointer priv_allocate(container_detail::true_type, Alloc &a, size_type n, const_void_pointer p)
      {  return a.allocate(n, p);  }

      static pointer priv_allocate(container_detail::false_type, Alloc &a, size_type n, const_void_pointer)
      {  return allocator_traits::allocate(a, n);  }

      template<class T>
      static void priv_destroy(container_detail::true_type, Alloc &a, T* p) BOOST_CONTAINER_NOEXCEPT
      {  a.destroy(p);  }

      template<class T>
      static void priv_destroy(container_detail::false_type, Alloc &, T* p) BOOST_CONTAINER_NOEXCEPT
      {  p->~T(); (void)p;  }

      static size_type priv_max_size(container_detail::true_type, const Alloc &a) BOOST_CONTAINER_NOEXCEPT
      {  return a.max_size();  }

      static size_type priv_max_size(container_detail::false_type, const Alloc &) BOOST_CONTAINER_NOEXCEPT
      {  return size_type(-1);  }

      static Alloc priv_select_on_container_copy_construction(container_detail::true_type, const Alloc &a)
      {  return a.select_on_container_copy_construction();  }

      static const Alloc &priv_select_on_container_copy_construction(container_detail::false_type, const Alloc &a) BOOST_CONTAINER_NOEXCEPT
      {  return a;  }

      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
         template<class T, class ...Args>
         static void priv_construct(container_detail::false_type, Alloc &a, T *p, BOOST_FWD_REF(Args) ...args)
         {
            const bool value = boost::container::container_detail::
                  has_member_function_callable_with_construct
                     < Alloc, T*, Args... >::value;
            container_detail::bool_<value> flag;
            priv_construct_dispatch2(flag, a, p, ::boost::forward<Args>(args)...);
         }

         template<class T, class ...Args>
         static void priv_construct(container_detail::true_type, Alloc &a, T *p, BOOST_FWD_REF(Args) ...args)
         {
            priv_construct_dispatch2(container_detail::false_type(), a, p, ::boost::forward<Args>(args)...);
         }

         template<class T, class ...Args>
         static void priv_construct_dispatch2(container_detail::true_type, Alloc &a, T *p, BOOST_FWD_REF(Args) ...args)
         {  a.construct( p, ::boost::forward<Args>(args)...);  }

         template<class T, class ...Args>
         static void priv_construct_dispatch2(container_detail::false_type, Alloc &, T *p, BOOST_FWD_REF(Args) ...args)
         {  ::new((void*)p, boost_container_new_t()) T(::boost::forward<Args>(args)...); }
      #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
         public:
         #define BOOST_PP_LOCAL_MACRO(n)                                                              \
         template<class T BOOST_PP_ENUM_TRAILING_PARAMS(n, class P) >                                 \
         static void construct(Alloc &a, T *p                                                         \
                              BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST, _))            \
         {                                                                                            \
            container_detail::bool_                                                                   \
               <container_detail::is_std_allocator<Alloc>::value> flag;                               \
            allocator_traits::priv_construct(flag, a, p                                               \
               BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _));                       \
         }                                                                                            \
         //
         #define BOOST_PP_LOCAL_LIMITS (0, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
         #include BOOST_PP_LOCAL_ITERATE()

         private:
         #define BOOST_PP_LOCAL_MACRO(n)                                                                    \
         template<class T  BOOST_PP_ENUM_TRAILING_PARAMS(n, class P) >                                      \
         static void priv_construct(container_detail::false_type, Alloc &a, T *p                            \
                        BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST,_))                         \
         {                                                                                                  \
            const bool value =                                                                              \
               boost::container::container_detail::has_member_function_callable_with_construct              \
                     < Alloc, T* BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_FWD_TYPE, _) >::value;        \
            container_detail::bool_<value> flag;                                                            \
            priv_construct_dispatch2(flag, a, p                                                             \
               BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _) );                            \
         }                                                                                                  \
                                                                                                            \
         template<class T  BOOST_PP_ENUM_TRAILING_PARAMS(n, class P) >                                      \
         static void priv_construct(container_detail::true_type, Alloc &a, T *p                             \
                        BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST,_))                         \
         {                                                                                                  \
            priv_construct_dispatch2(container_detail::false_type(), a, p                                   \
               BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _) );                            \
         }                                                                                                  \
                                                                                                            \
         template<class T  BOOST_PP_ENUM_TRAILING_PARAMS(n, class P) >                                      \
         static void priv_construct_dispatch2(container_detail::true_type, Alloc &a, T *p                   \
                        BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST,_))                         \
         {  a.construct( p BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _) );  }             \
                                                                                                            \
         template<class T  BOOST_PP_ENUM_TRAILING_PARAMS(n, class P) >                                      \
         static void priv_construct_dispatch2(container_detail::false_type, Alloc &, T *p                   \
                        BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST, _) )                       \
         {  ::new((void*)p, boost_container_new_t()) T(BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _)); }\
         //
         #define BOOST_PP_LOCAL_LIMITS (0, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
         #include BOOST_PP_LOCAL_ITERATE()
      #endif   // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

      template<class T>
      static void priv_construct_dispatch2(container_detail::false_type, Alloc &, T *p, ::boost::container::default_init_t)
      {  ::new((void*)p) T; }
   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

}  //namespace container {
}  //namespace boost {

#include "boost/container/detail/config_end.hpp"

#endif // ! defined(BOOST_CONTAINER_ALLOCATOR_ALLOCATOR_TRAITS_HPP)
