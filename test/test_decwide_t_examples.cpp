#include <math/wide_decimal/decwide_t.h>

bool test_decwide_t_examples()
{
  bool result_is_ok = true;

  result_is_ok &= math::wide_decimal::example001_sqrt();
  result_is_ok &= math::wide_decimal::example002_pi  ();

  return result_is_ok;
}