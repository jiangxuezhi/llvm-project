//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <forward_list>

// explicit forward_list(const allocator_type& a); // constexpr since C++26

#include <forward_list>
#include <cassert>

#include "test_macros.h"
#include "test_allocator.h"
#include "../../../NotConstructible.h"
#include "min_allocator.h"

TEST_CONSTEXPR_CXX26 bool test() {
  {
    typedef test_allocator<NotConstructible> A;
    typedef A::value_type T;
    typedef std::forward_list<T, A> C;
    C c(A(12));
    assert(c.get_allocator() == A(12));
    assert(c.empty());
  }
#if TEST_STD_VER >= 11
  {
    typedef min_allocator<NotConstructible> A;
    typedef A::value_type T;
    typedef std::forward_list<T, A> C;
    C c(A{});
    assert(c.get_allocator() == A());
    assert(c.empty());
  }
  {
    typedef explicit_allocator<NotConstructible> A;
    typedef A::value_type T;
    typedef std::forward_list<T, A> C;
    C c(A{});
    assert(c.get_allocator() == A());
    assert(c.empty());
  }
#endif

  return true;
}

int main(int, char**) {
  assert(test());
#if TEST_STD_VER >= 26
  static_assert(test());
#endif

  return 0;
}
