///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// On Windows Subsystem for LINUX
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/wide_decimal
// When using g++-10 and -std=c++20
// g++-10 -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++20 -DWIDE_DECIMAL_NAMESPACE=ckormanyos -I. -I/mnt/c/boost/boost_1_78_0 -pthread -lpthread test/test.cpp test/test_decwide_t_algebra.cpp test/test_decwide_t_examples.cpp examples/example000a_multiply_pi_squared.cpp examples/example000_multiply_nines.cpp examples/example001_roots_sqrt.cpp examples/example001a_roots_seventh.cpp examples/example001b_roots_almost_integer.cpp examples/example001c_roots_sqrt_limb08.cpp examples/example001d_pow2_from_list.cpp examples/example002_pi.cpp examples/example002a_pi_small_limb.cpp examples/example002b_pi_100k.cpp examples/example002c_pi_quintic.cpp examples/example002d_pi_limb08.cpp examples/example003_zeta.cpp examples/example004_bessel_recur.cpp examples/example005_polylog_series.cpp examples/example006_logarithm.cpp examples/example007_catalan_series.cpp examples/example008_bernoulli_tgamma.cpp examples/example009_boost_math_standalone.cpp examples/example009a_boost_math_standalone.cpp examples/example009b_boost_math_standalone.cpp examples/example010_hypergeometric_2f1.cpp examples/example010a_hypergeometric_1f1.cpp examples/example011_trig_trapezoid_integral.cpp examples/example012_rational_floor_ceil.cpp examples/example013_embeddable_sqrt.cpp examples/example013a_embeddable_agm.cpp -o wide_decimal.exe

// cd .tidy/make
// make prepare -f make_tidy_01_generic.gmk MY_BOOST_ROOT=/mnt/c/boost/boost_1_78_0
// make tidy -f make_tidy_01_generic.gmk --jobs=8 MY_BOOST_ROOT=/mnt/c/boost/boost_1_78_0

// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/wide_decimal
// PATH=/home/chris/local/coverity/cov-analysis-linux64-2021.12.1/bin:$PATH
// cov-build --dir cov-int g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-cast-function-type -std=c++11 -DWIDE_DECIMAL_NAMESPACE=ckormanyos -I. -I/mnt/c/boost/boost_1_78_0 -pthread -lpthread test/test.cpp test/test_decwide_t_algebra.cpp test/test_decwide_t_examples.cpp examples/example000a_multiply_pi_squared.cpp examples/example000_multiply_nines.cpp examples/example001_roots_sqrt.cpp examples/example001a_roots_seventh.cpp examples/example001b_roots_almost_integer.cpp examples/example001c_roots_sqrt_limb08.cpp examples/example001d_pow2_from_list.cpp examples/example002_pi.cpp examples/example002a_pi_small_limb.cpp examples/example002b_pi_100k.cpp examples/example002c_pi_quintic.cpp examples/example002d_pi_limb08.cpp examples/example003_zeta.cpp examples/example004_bessel_recur.cpp examples/example005_polylog_series.cpp examples/example006_logarithm.cpp examples/example007_catalan_series.cpp examples/example008_bernoulli_tgamma.cpp examples/example009_boost_math_standalone.cpp examples/example009a_boost_math_standalone.cpp examples/example009b_boost_math_standalone.cpp examples/example010_hypergeometric_2f1.cpp examples/example010a_hypergeometric_1f1.cpp examples/example011_trig_trapezoid_integral.cpp examples/example012_rational_floor_ceil.cpp examples/example013_embeddable_sqrt.cpp examples/example013a_embeddable_agm.cpp -o wide_decimal.exe
// tar caf wide-decimal.bz2 cov-int

#include <chrono>
#include <iomanip>
#include <iostream>

#include <boost/version.hpp>

#if !defined(BOOST_VERSION)
#error BOOST_VERSION is not defined. Ensure that <boost/version.hpp> is properly included.
#endif

#if ((BOOST_VERSION < 107900) && defined(__GNUC__))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#if (BOOST_VERSION < 107900)
#include <boost/math/policies/error_handling.hpp>
#include <boost/throw_exception.hpp>
#endif

#include <test/test_decwide_t_algebra.h>
#include <test/test_decwide_t_examples.h>

namespace local
{
  auto run() -> bool;
} // namespace local

auto local::run() -> bool
{
  #if (BOOST_VERSION < 107900)
  using boost_wrapexcept_round_type  = ::boost::wrapexcept<::boost::math::rounding_error>;
  using boost_wrapexcept_domain_type = ::boost::wrapexcept<std::domain_error>;
  #endif

  #if defined(WIDE_DECIMAL_NAMESPACE)
  using namespace WIDE_DECIMAL_NAMESPACE;
  #else
  #endif

  using local_clock_type = std::chrono::high_resolution_clock;
  using time_point_type  = typename local_clock_type::time_point;

  auto start = time_point_type();
  auto stop  = time_point_type();

  bool result_is_ok { };

  #if (BOOST_VERSION < 107900)
  try
  {
  #endif
  start = local_clock_type::now(); const bool result_test_decwide_t_examples_part1_is_ok = (test_decwide_t_examples_part1__()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_examples_part1_is_ok: " << std::boolalpha << result_test_decwide_t_examples_part1_is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_examples_part2_is_ok = (test_decwide_t_examples_part2__()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_examples_part2_is_ok: " << std::boolalpha << result_test_decwide_t_examples_part2_is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_add____is_ok = (test_decwide_t_algebra_add_____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_add____is_ok: " << std::boolalpha << result_test_decwide_t_algebra_add____is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_sub____is_ok = (test_decwide_t_algebra_sub_____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_sub____is_ok: " << std::boolalpha << result_test_decwide_t_algebra_sub____is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_mul____is_ok = (test_decwide_t_algebra_mul_____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_mul____is_ok: " << std::boolalpha << result_test_decwide_t_algebra_mul____is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_div____is_ok = (test_decwide_t_algebra_div_____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_div____is_ok: " << std::boolalpha << result_test_decwide_t_algebra_div____is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_sqrt___is_ok = (test_decwide_t_algebra_sqrt____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_sqrt___is_ok: " << std::boolalpha << result_test_decwide_t_algebra_sqrt___is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
  start = local_clock_type::now(); const bool result_test_decwide_t_algebra_log____is_ok = (test_decwide_t_algebra_log_____()); stop = local_clock_type::now(); std::cout << "result_test_decwide_t_algebra_log____is_ok: " << std::boolalpha << result_test_decwide_t_algebra_log____is_ok << ", time: " << (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())) / 1000.0F << "s" << std::endl; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)

  result_is_ok = (   result_test_decwide_t_examples_part1_is_ok
                  && result_test_decwide_t_examples_part2_is_ok
                  && result_test_decwide_t_algebra_add____is_ok
                  && result_test_decwide_t_algebra_sub____is_ok
                  && result_test_decwide_t_algebra_mul____is_ok
                  && result_test_decwide_t_algebra_div____is_ok
                  && result_test_decwide_t_algebra_sqrt___is_ok
                  && result_test_decwide_t_algebra_log____is_ok);
  #if (BOOST_VERSION < 107900)
  }
  catch(boost_wrapexcept_round_type& e)
  {
    result_is_ok = false;

    std::cout << "Exception: boost_wrapexcept_round_type: " << e.what() << std::endl;
  }
  catch(boost_wrapexcept_domain_type& e)
  {
    result_is_ok = false;

    std::cout << "Exception: boost_wrapexcept_domain_type: " << e.what() << std::endl;
  }
  #endif

  return result_is_ok;
}

auto main() -> int
{
  using local_clock_type = std::chrono::high_resolution_clock;

  const auto start = local_clock_type::now();

  const auto result_is_ok = local::run();

  const auto stop = local_clock_type::now();

  {
    constexpr auto one_thousand_milliseconds = 1000.0F;

    const auto test_duration_sec =
      static_cast<float>
      (
        static_cast<float>
        (
          std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
        )
        / one_thousand_milliseconds
      );

    const auto flg = std::cout.flags();

    std::cout << "result_is_ok:                             : "
              << std::boolalpha
              << result_is_ok
              << ", time: "
              << test_duration_sec
              << "s"
              << std::endl
              ;

    std::cout.flags(flg);
  }

  return (result_is_ok ? 0 : -1);
}

#if ((BOOST_VERSION < 107900) && defined(__GNUC__))
#pragma GCC diagnostic pop
#endif
