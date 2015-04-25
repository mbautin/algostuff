#pragma once

inline long long compute_gcd(long long a, long long b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;

  while (a != 0 && b != 0) {
    if (a > b)
      a %= b;
    else
      b %= a;
  }
  return a + b;
};

class RationalNumber {
public:
  RationalNumber(): n(0), d(1) {}
  RationalNumber(long long _n): n(_n), d(1) {}

  RationalNumber(long long _n, long long _d):
    n(_n),
    d(_d) {
    simplify();
  }

  long numerator() { return n; }
  long denominator() { return d; }

  friend RationalNumber operator +(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator -(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator *(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator /(const RationalNumber&, const RationalNumber&);
  friend bool operator ==(const RationalNumber&, const RationalNumber&);

private:
  long long n;
  long long d;

  inline void simplify() {
    long long gcd = compute_gcd(n, d);
    if (d < 0) gcd = -gcd;  // Ensure we end up with a positive denominator.
    n /= gcd;
    d /= gcd;
  }
};

RationalNumber operator +(const RationalNumber& a, const RationalNumber& b) {
  return RationalNumber(a.n * b.d + b.n * a.d, a.d * b.d);
};

RationalNumber operator -(const RationalNumber& a, const RationalNumber& b) {
  return RationalNumber(a.n * b.d - b.n * a.d, a.d * b.d);
};

RationalNumber operator *(const RationalNumber& a, const RationalNumber& b) {
  return RationalNumber(a.n * b.n, a.d * b.d);
};

RationalNumber operator /(const RationalNumber& a, const RationalNumber& b) {
  return RationalNumber(a.n * b.d, a.d * b.n);
};

bool operator ==(const RationalNumber& a, const RationalNumber& b) {
  // We assume that both operands have been simplified as much as possible.
  return a.n == b.n && a.d == b.d;
};

class Vector {
public:
  Vector(RationalNumber* _backing_array, bool _own_array, int _step):
    backing_array(_backing_array),
    own_array(_own_array),
    step(_step) {
  }

private:
  RationalNumber* backing_array;
  bool own_array;
  int step;
};

class Matrix {
public:
  Matrix(int _m, int _n): m(_m), n(_n) {
    rows = new RationalNumber[m * n];
  }

  virtual ~Matrix() {
    delete[] rows;
  }
private:
  int m;  // height
  int n;  // width
  RationalNumber* rows;
};
