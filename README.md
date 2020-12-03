# Wide-decimal
Wide-decimal implements a generic C++ template for extended precision decimal float types.

This C++ template header-only library implements drop-in big decimal float types such as `dec101_t`, `dec10001_t`, `dec1000001_t`, etc., that can be used essentially like regular built-in floating-point types. Wide-decimal supports decimal float types having digit counts ranging from about <img src="https://render.githubusercontent.com/render/math?math=30{\ldots}1,000,000">.

Wide-decimal implements both common algebraic operations as well as a few common `<cmath>` functions such as `fabs`, `sqrt` and `log`, and also includes full support for `std::numeric_limits`.

Wide-decimal is written in header-only C++11.

# Implementation goals

  - wide precision range up to one million decimal digits,
  - moderately good efficiency over the entire wide precision range,
  - clean header-only C++11 design.
  - seamless portability to any modern C++11 compiler,
  - scalability with small memory footprint appropriate for _bare-metal_ embedded systems.

# The examples

  - ![`example001_roots_sqrt`](./examples/example001_roots_sqrt.cpp) computes a square root.
  - ![`example001a_roots_seventh`](./examples/example001a_roots_seventh.cpp) computes a seventh root.
  - ![`example002_pi`](./examples/example002_pi.cpp) calculates <img src="https://render.githubusercontent.com/render/math?math=1,000,001"> decimal digits of <img src="https://render.githubusercontent.com/render/math?math=\pi">.
  - ![`example002a_pi_small_limb`](./examples/example002a_pi_small_limb.cpp) calculates <img src="https://render.githubusercontent.com/render/math?math=1,000,001"> decimal digits of <img src="https://render.githubusercontent.com/render/math?math=\pi"> using a 16-bit internal limb type.
  - ![`example002b_pi_100k`](./examples/example002b_pi_100k.cpp) calculates <img src="https://render.githubusercontent.com/render/math?math=100,001"> decimal digits of <img src="https://render.githubusercontent.com/render/math?math=\pi">.
  - ![`example003_zeta`](./examples/example003_zeta.cpp) computes a Riemann zeta function value.
  - ![`example004_bessel_recur`](./examples/example004_bessel_recur.cpp) implements cylindrical Bessel functions of integral order via downward recursion with a Neumann sum.
  - ![`example005_polylog_series`](./examples/example005_polylog_series.cpp) performs a small-argument polylogarithm series calculation.
  - ![`example006_logarithm`](./examples/example006_logarithm.cpp) calculates the value of a logarithm (internally using a Gauss AGM method).
  - ![`example007_catalan_series`](./examples/example007_catalan_series.cpp) compuste <img src="https://render.githubusercontent.com/render/math?math=1,001"> decimal digits of Catalan's constant using an accelerated series.

# 1,000,000 digits of pi on bare metal

The wide-decimal float back end is used to compute
<img src="https://render.githubusercontent.com/render/math?math=1,000,000">
decimal digits of the mathematical constant
<img src="https://render.githubusercontent.com/render/math?math=\pi">
on bare-metal OS-less microcontroller systems in
[pi-crunch-metal](https://github.com/ckormanyos/pi-crunch-metal)

# Details
Wide-Decimal has been tested with numerous compilers for target systems ranging from 8 to 64 bits.
The library is specifically designed for modest efficiency (not the world's fastest)
over the entire range of small to large digit counts.

Portability of the code is another key point of focus. Special care
has been taken to test in certain high-performance embedded real-time
programming environments.

Testing is a big issue. Generating a full test suite is in continued progress
and tested efficient functionality on the PC and workstation is present.
The code is delivered with an affiliated MSVC project that uses Boost.Test
for various test cases.

When working with even the most tiny microcontroller systems,
various _heavy-wieght_ features such as I/O streaming,
conversion to and from built-in floating-point types
and construction from character string
can optionally be disabled with the compiler switches:

```
#define WIDE_DECIMAL_DISABLE_IOSTREAM
#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
#define WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
```

Note: Activating the option `WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION`
simultaneously disallows using `decwide_t` in a multithreaded application.
So if PC-based multithreading is needed, then dynamic memory
allocation needs to be used.

See the examples directory as more use cases are being created.

# Quick start
Easy application follows via a traditional C-style typedef or C++11 alias.
The defined type can be used very much like a built-in floating-point type.

The following sample, for instance, defines and uses a decimal type
called `dec101_t` having
<img src="https://render.githubusercontent.com/render/math?math=101">
decimal digits of precision.

```
#include <iomanip>
#include <iostream>

#include <math/wide_decimal/decwide_t.h>

void do_something()
{
  using dec101_t = math::wide_decimal::decwide_t<101U, std::uint32_t>;

  dec101_t d = dec101_t(1) / 3;

  // 0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
  std::cout << std::setprecision(std::numeric_limits<dec101_t>::digits) << d << std::endl;
}
```

The local data type `dec101_t` is defined with a C++11 alias.
The first template parameter `101U` sets the decimal digit
count while the second optional template parameter `std::uint32_t`
sets the internal _limb_ _type_. If the second template parameter is left blank,
the default limb type is 32 bits in width and unsigned.
The subroutine `do_something()` initializes the variable `d`
of type `dec101_t` with 1/3 and subsequently prints the 101 digit
value of `d` to the console.

# Detailed examples

The example below calculates the square root of the decimal representation of
<img src="https://render.githubusercontent.com/render/math?math=\sqrt{1234.56}">,
the result of which is approximately
<img src="https://render.githubusercontent.com/render/math?math=35.136306009596398663933384640418055759751518287169314528165976164717710895452890928635031219132220\ldots">.

```
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include <math/wide_decimal/decwide_t.h>

int main()
{
  using dec101_t = math::wide_decimal::decwide_t<101U>;

  const dec101_t a(1234U);
  const dec101_t b(dec101_t(56U) / 100U);

  const dec101_t s = sqrt(a + b);

  constexpr std::array<typename dec101_t::limb_type, 13U> control =
  {
    35,
    13630600,
    95963986,
    63933384,
    64041805,
    57597515,
    18287169,
    31452816,
    59761647,
    17710895,
    45289092,
    86350312,
    19132220
  };

  const bool result_is_ok = std::equal(s.crepresentation().cbegin(),
                                       s.crepresentation().cbegin() + control.size(),
                                       control.cbegin());

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

In the following code, we compute <img src="https://render.githubusercontent.com/render/math?math=1,000,001">
(one million and one) decimal digits of the fundamental constant
<img src="https://render.githubusercontent.com/render/math?math=\pi">.
The truncated (non-rounded) expected result is
<img src="https://render.githubusercontent.com/render/math?math=3.14159265\,\ldots\,79458151">.
In this particular example, all _heavy-weight_ components are deactivated and
this particular calculation is, in fact, suitable for a _bare-metal_ mega-digit pi calculation.

In this example, note how a specialized custom allocator called
`util::n_slot_array_allocator` is utilized for exact memory management
of a certain number of temporary storages of mega-digit numbers
(tuned to 18 in this particular example).

```
#include <array>
#include <iomanip>
#include <iostream>

#define WIDE_DECIMAL_DISABLE_IOSTREAM
#define WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING

#include <math/wide_decimal/decwide_t.h>
#include <util/memory/util_n_slot_array_allocator.h>

int main()
{
  using local_limb_type = std::uint32_t;

  constexpr std::uint32_t wide_decimal_digits10 = UINT32_C(1000001);

  constexpr std::int32_t local_elem_number =
    math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;

  using local_allocator_type = util::n_slot_array_allocator<void, local_elem_number, 18U>;

  // Calculate pi.
  math::wide_decimal::decwide_t<wide_decimal_digits10, local_limb_type, local_allocator_type, double> my_pi =
    math::wide_decimal::pi<wide_decimal_digits10, local_limb_type, local_allocator_type, double>();

  constexpr std::array<local_limb_type, 8U> control_head =
  {{
    local_limb_type(3ULL),
    local_limb_type(14159265ULL),
    local_limb_type(35897932ULL),
    local_limb_type(38462643ULL),
    local_limb_type(38327950ULL),
    local_limb_type(28841971ULL),
    local_limb_type(69399375ULL),
    local_limb_type(10582097ULL)
  }};

  constexpr std::array<local_limb_type, 8U> control_tail =
  {{
    local_limb_type(20875424ULL),
    local_limb_type(50598956ULL),
    local_limb_type(78796130ULL),
    local_limb_type(33116462ULL),
    local_limb_type(83996346ULL),
    local_limb_type(46042209ULL),
    local_limb_type( 1061057ULL),
    local_limb_type(79458151ULL)
  }};

  // Verify the pi result at the front and back.
  const bool head_is_ok = std::equal(my_pi.crepresentation().cbegin(),
                                     my_pi.crepresentation().cbegin() + control_head.size(),
                                     control_head.cbegin());

  const bool tail_is_ok = std::equal(my_pi.crepresentation().cbegin() + 125001UL - 8UL,
                                     my_pi.crepresentation().cbegin() + 125001UL,
                                     control_tail.cbegin());

  const bool result_is_ok = (head_is_ok && tail_is_ok);

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}
```

The million digit run is comparatively slow and requires approximately
10 seconds on a modern PC. Considering, however, the design goals
of header-only and capable of running on bare-metal, this is
a very nice calculational result.
