#include "linalg_playground.h"

#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, char** argv) {
  assert(compute_gcd(5, 15) == 5);
  assert(compute_gcd(15, 5) == 5);
  assert(compute_gcd(100, -50) == 50);
  assert(compute_gcd(-256, 192) == 64);
  assert(RationalNumber(1, 3) + RationalNumber(2, 3) == RationalNumber(1, 1));
  assert(RationalNumber(1, 2) + RationalNumber(1, 3) == RationalNumber(5, 6));
  assert(RationalNumber(1, 2) - RationalNumber(1, 3) == RationalNumber(1, 6));
  assert(RationalNumber(1, 3) * RationalNumber(2, 3) == RationalNumber(2, 9));
  assert(RationalNumber(1, 3) - RationalNumber(1, 3) == RationalNumber(0, 1));
  // Automatic conversion from integers to rational numbers.
  assert(RationalNumber(1, 1) == 1);
  assert(RationalNumber(50, 10) == 5);
  assert(5 == RationalNumber(50, 10));

  // Matrix tests.
  Matrix m(3, 4);
  m.set_element_at(0, 0, 5);
  assert(m.element_at(0, 0) == 5);

  m.set_element_at(2, 1, 6);
  assert(m.element_at(2, 1) == 6);

  m.set_element_at(2, 2, RationalNumber(2, 3));
  assert(m.element_at(2, 2) == RationalNumber(2, 3));

  cout << "Test matrix:" << endl;
  cout << m;

  cout << "All tests succeeded" << endl;
}
