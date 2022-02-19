﻿///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef DECWIDE_T_2021_02_24_HPP
  #define DECWIDE_T_2021_02_24_HPP

  #include <boost/version.hpp>

  #include <math/wide_decimal/decwide_t.h>

  #if !defined(BOOST_VERSION)
  #error BOOST_VERSION is not defined. Ensure that <boost/version.hpp> is properly included.
  #endif

  #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107600))
  #include <boost/math/bindings/detail/big_lanczos.hpp>
  #endif
  #include <boost/math/constants/constants.hpp>
  #include <boost/math/policies/policy.hpp>
  #include <boost/math/special_functions/sign.hpp>

  #if(__cplusplus >= 201703L)
  namespace boost::math {
  #else
  namespace boost { namespace math { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace policies {

  // Specialization of the precision structure.
  template<const std::int32_t MyDigitsBase10,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType,
           typename ThisPolicy>
  #if defined(WIDE_DECIMAL_NAMESPACE)
  struct precision<::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>, ThisPolicy>
  #else
  struct precision<::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>, ThisPolicy>
  #endif
  {
    #if defined(WIDE_DECIMAL_NAMESPACE)
    using local_wide_decimal_type =
      ::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
    #else
    using local_wide_decimal_type =
      ::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
    #endif

    using precision_type = typename ThisPolicy::precision_type;

    using local_digits_2 = digits2<((static_cast<long long>(std::numeric_limits<local_wide_decimal_type>::digits10) + 1LL) * 1000LL) / 301LL>; // NOLINT(google-runtime-int)

    using type = typename std::conditional<((local_digits_2::value <= precision_type::value) || (precision_type::value <= 0)),
                                            local_digits_2,
                                            precision_type>::type;
  };

  } // namespace policies

  #if(__cplusplus >= 201703L)
  namespace constants::detail {
  #else
  namespace constants { namespace detail { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template <class T>
  struct constant_pi;

  template<const std::int32_t MyDigitsBase10,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  #if defined(WIDE_DECIMAL_NAMESPACE)
  struct constant_pi<::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
  #else
  struct constant_pi<::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
  #endif
  {
  public:
    #if defined(WIDE_DECIMAL_NAMESPACE)
    using result_type =
      ::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
    #else
    using result_type =
      ::math::wide_decimal::decwide_t<MyDigitsBase10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
    #endif

  private:
    static auto my_compute() -> result_type
    {
      // Adapted from Boost.Math.Constants (see file calculate_constants.hpp).

      result_type result;
      result_type a(1U);
      result_type b;
      result_type A(a);
      result_type B(0.5F);
      result_type D(0.25F);

      result_type lim = std::numeric_limits<result_type>::epsilon();

      auto k = static_cast<unsigned>(1U);

      do
      {
        using std::ldexp;
        using std::sqrt;

        result = A + B;
        result = ldexp(result, -2);
        b = sqrt(B);
        a += b;
        a = ldexp(a, -1);
        A = a * a;
        B = A - result;
        B = ldexp(B, 1);
        result = A - B;

        const bool neg = (boost::math::sign(result) < 0);

        if(neg)
        {
          result = -result;
        }

        if(result <= lim)
        {
          break;
        }

        if(neg)
        {
          result = -result;
        }

        result = ldexp(result, k - 1);
        D -= result;
        ++k;
        lim = ldexp(lim, 1);
      }
      while(true);

      result = B / D;

      return result;
    }

  public:
    #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107200))
    template<int N> static auto get(const mpl::int_<N>&) -> const result_type& // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #elif (defined(BOOST_VERSION) && (BOOST_VERSION <= 107500))
    template<int N> static auto get(const boost::integral_constant<int, N>&) -> const result_type& // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #else
    template<int N> static auto get(const std::integral_constant<int, N>&) -> const result_type& // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #endif // BOOST_VERSION
    {
      static result_type result;
      static bool        has_init = false;

      if(!has_init)
      {
        has_init = true;

        result = my_compute();
      }

      return result;
    }

    #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107200))
    static inline auto get(const mpl::int_<0>&) -> result_type // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #elif (defined(BOOST_VERSION) && (BOOST_VERSION <= 107500))
    static inline auto get(const boost::integral_constant<int, 0>&) -> result_type // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #else
    static inline auto get(const std::integral_constant<int, 0>&) -> result_type // NOLINT(hicpp-named-parameter,readability-named-parameter)
    #endif // BOOST_VERSION
    {
      return my_compute();
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace constants::detail
  #else
  } // namespace detail
  } // namespace constants
  #endif

  #if (defined(BOOST_VERSION) && (BOOST_VERSION <= 107600))
  namespace lanczos {

  template <typename T, typename Policy>
  struct lanczos;

  template<const std::int32_t MyDigitsBase10,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType,
           typename Policy>
  #if defined(WIDE_DECIMAL_NAMESPACE)
  struct lanczos<::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10,
  #else
  struct lanczos<::math::wide_decimal::decwide_t<MyDigitsBase10,
  #endif
                                                 LimbType,
                                                 AllocatorType,
                                                 InternalFloatType,
                                                 ExponentType,
                                                 FftFloatType>,
                 Policy>
  {
    using local_backend_type =
      #if defined(WIDE_DECIMAL_NAMESPACE)
      ::WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<MyDigitsBase10,
      #else
      ::math::wide_decimal::decwide_t<MyDigitsBase10,
      #endif
                                      LimbType,
                                      AllocatorType,
                                      InternalFloatType,
                                      ExponentType,
                                      FftFloatType>;

    using precision_type =
      typename boost::math::policies::precision<local_backend_type, Policy>::type;

    using type =
      typename std::conditional<precision_type::value && (precision_type::value <= 73),
                                lanczos13UDT,
                                typename std::conditional<precision_type::value && (precision_type::value <= 122),
                                                          lanczos22UDT,
                                                          undefined_lanczos>::type>::type;
  };

  } // namespace lanczos
  #endif // BOOST_VERSION

  #if(__cplusplus >= 201703L)
  } // namespace boost::math
  #else
  } // namespace math
  } // namespace boost
  #endif

#endif // DECWIDE_T_2021_02_24_HPP
