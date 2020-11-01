///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469


// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\wide_decimal
// g++ -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -pedantic -Wno-cast-function-type -std=c++11 -I. -IC:/boost/boost_1_73_0 test/test.cpp test/test_decwide_t_algebra.cpp test/test_decwide_t_examples.cpp examples/example001_sqrt.cpp examples/example002_pi.cpp examples/example003_zeta.cpp -o wide_decimal.exe

#include <iomanip>
#include <iostream>

#define BOOST_TEST_MODULE test_decwide_t
#include <boost/test/included/unit_test.hpp>

bool test_decwide_t_algebra_add_();
bool test_decwide_t_algebra_sub_();
bool test_decwide_t_algebra_mul_();
bool test_decwide_t_algebra_div_();
bool test_decwide_t_algebra_sqrt();
bool test_decwide_t_examples();

BOOST_AUTO_TEST_CASE(test_decwide_t_examples_tag)
{
  std::cout << "running: test_decwide_t_examples" << std::endl;
  const bool result_test_decwide_t_examples_is_ok = test_decwide_t_examples();
  BOOST_CHECK(result_test_decwide_t_examples_is_ok);
}

BOOST_AUTO_TEST_CASE(test_decwide_t_algebra_add__tag)
{
  std::cout << "running: test_decwide_t_algebra_add_" << std::endl;
  const bool result_test_decwide_t_algebra_add__is_ok = test_decwide_t_algebra_add_();
  BOOST_CHECK(result_test_decwide_t_algebra_add__is_ok);
}

BOOST_AUTO_TEST_CASE(test_decwide_t_algebra_sub__tag)
{
  std::cout << "running: test_decwide_t_algebra_sub_" << std::endl;
  const bool result_test_decwide_t_algebra_sub__is_ok = test_decwide_t_algebra_sub_();
  BOOST_CHECK(result_test_decwide_t_algebra_sub__is_ok);
}

BOOST_AUTO_TEST_CASE(test_decwide_t_algebra_mul__tag)
{
  std::cout << "running: test_decwide_t_algebra_mul_" << std::endl;
  const bool result_test_decwide_t_algebra_mul__is_ok = test_decwide_t_algebra_mul_();
  BOOST_CHECK(result_test_decwide_t_algebra_mul__is_ok);
}

BOOST_AUTO_TEST_CASE(test_decwide_t_algebra_div__tag)
{
  std::cout << "running: test_decwide_t_algebra_div_" << std::endl;
  const bool result_test_decwide_t_algebra_div__is_ok = test_decwide_t_algebra_div_();
  BOOST_CHECK(result_test_decwide_t_algebra_div__is_ok);
}

BOOST_AUTO_TEST_CASE(test_decwide_t_algebra_sqrt_tag)
{
  std::cout << "running: test_decwide_t_algebra_sqrt" << std::endl;
  const bool result_test_decwide_t_algebra_sqrt_is_ok = test_decwide_t_algebra_sqrt();
  BOOST_CHECK(result_test_decwide_t_algebra_sqrt_is_ok);
}
