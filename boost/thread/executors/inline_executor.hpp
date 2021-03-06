// Copyright (C) 2014 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// 2013/11 Vicente J. Botet Escriba
//    first implementation of a simple serial scheduler.

#ifndef BOOST_THREAD_INLINE_EXECUTOR_HPP
#define BOOST_THREAD_INLINE_EXECUTOR_HPP

#include "boost/thread/detail/config.hpp"
#include "boost/thread/detail/delete.hpp"
#include "boost/thread/detail/move.hpp"
#include "boost/thread/executors/work.hpp"

#include "boost/config/abi_prefix.hpp"

namespace boost
{
namespace executors
{
  class inline_executor
  {
  public:
    /// type-erasure to store the works to do
    typedef  executors::work work;
    bool closed_;
    /**
     * Effects: try to execute one task.
     * Returns: whether a task has been executed.
     * Throws: whatever the current task constructor throws or the task() throws.
     */
    bool try_executing_one()
    {
      return false;
    }

  public:
    /// inline_executor is not copyable.
    BOOST_THREAD_NO_COPYABLE(inline_executor)

    /**
     * \b Effects: creates a inline executor that runs closures immediately.
     *
     * \b Throws: Nothing.
     */
    inline_executor()
    : closed_(false)
    {
    }
    /**
     * \b Effects: Destroys the inline executor.
     *
     * \b Synchronization: The completion of all the closures happen before the completion of the \c inline_executor destructor.
     */
    ~inline_executor()
    {
      // signal to all the worker thread that there will be no more submissions.
      close();
    }

    /**
     * \b Effects: close the \c inline_executor for submissions.
     * The loop will work until there is no more closures to run.
     */
    void close()
    {
      closed_ = true;
    }

    /**
     * \b Returns: whether the pool is closed for submissions.
     */
    bool closed()
    {
      return closed_;
    }

    /**
     * \b Requires: \c Closure is a model of \c Callable(void()) and a model of \c CopyConstructible/MoveConstructible.
     *
     * \b Effects: The specified \c closure will be scheduled for execution at some point in the future.
     * If invoked closure throws an exception the \c inline_executor will call \c std::terminate, as is the case with threads.
     *
     * \b Synchronization: completion of \c closure on a particular thread happens before destruction of thread's thread local variables.
     *
     * \b Throws: \c sync_queue_is_closed if the thread pool is closed.
     * Whatever exception that can be throw while storing the closure.
     */

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename Closure>
    void submit(Closure & closure)
    {
      if (closed()) return;
      closure();
    }
#endif
    void submit(void (*closure)())
    {
      if (closed()) return;
      closure();
    }

    template <typename Closure>
    void submit(BOOST_THREAD_FWD_REF(Closure) closure)
    {
      if (closed()) return;
      closure();
    }

    /**
     * \b Requires: This must be called from an scheduled task.
     *
     * \b Effects: reschedule functions until pred()
     */
    template <typename Pred>
    bool reschedule_until(Pred const& )
    {
      return false;
    }

  };
}
using executors::inline_executor;
}

#include "boost/config/abi_suffix.hpp"

#endif
