// Copyright (C) 2009 by Thomas Moulard, FIXME.
//
// This file is part of the liboptimization.
//
// liboptimization is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// liboptimization is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with liboptimization.  If not, see <http://www.gnu.org/licenses/>.

#include "common.hh"
#include <liboptimization/derivable-function.hh>
#include <liboptimization/problem.hh>

using namespace optimization;

struct F : public DerivableFunction
{
public:
  F () throw () : DerivableFunction (1, 1)
  {}

  virtual vector_t
  operator () (const vector_t&) const throw ()
  {
    vector_t res (m);
    res.clear ();
    return res;
  }

  virtual gradient_t
  gradient (const vector_t& x, int) const throw ()
  {
    gradient_t grad (n);
    grad.clear ();
    return grad;
  }
};

// Check that a problem has really been copied.
#define CHECK_COPY(A, B)                                                \
  assert (&(A).function () == &(B).function ());                        \
  assert ((A).constraints ().size () == (B).constraints ().size ());    \
                                                                        \
  for (unsigned i = 0; i < (A).constraints ().size (); ++i)             \
    assert ((A).constraints ()[i] == (B).constraints ()[i])

int run_test ()
{
  typedef Problem<DerivableFunction, const DerivableFunction*> problemSrc_t;
  typedef Problem<Function, const Function*> problemDst_t;

  F f;

  problemSrc_t pbSrc (f);

  // Check with same type.
  {
    problemSrc_t pbDst (pbSrc);
    CHECK_COPY(pbSrc, pbDst);
  }

  // Check with a more general type.
  {
    problemDst_t pbDst (pbSrc);
    CHECK_COPY(pbSrc, pbDst);
  }

  return 0;
}

GENERATE_TEST ()
