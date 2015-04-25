#pragma once

#include "assert.h"

#include <ostream>
#include <iostream>  // TODO: delete this

inline long long compute_gcd(long long a, long long b) {
  // Euclid's algorithm
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

  long numerator() const { return n; }
  long denominator() const { return d; }

  friend RationalNumber operator +(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator -(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator *(const RationalNumber&, const RationalNumber&);
  friend RationalNumber operator /(const RationalNumber&, const RationalNumber&);
  friend bool operator ==(const RationalNumber&, const RationalNumber&);

  RationalNumber& operator =(RationalNumber& that) {
    n = that.n;
    d = that.d;
    *this;
  }

  RationalNumber& operator =(const RationalNumber& that) {
    n = that.n;
    d = that.d;
    *this;
  }

  RationalNumber& operator =(long long value) {
    n = value;
    d = 1;
    *this;
  }

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

std::ostream& operator << (std::ostream& out, const RationalNumber& x) {
  out << x.numerator();
  long long d = x.denominator();
  if (d != 1) {
    out << "/" << d;
  }
  return out;
}

class Vector {
public:
  Vector(RationalNumber* _backing_array, bool _own_array, int _step, int _size):
    backing_array(_backing_array),
    own_array(_own_array),
    step(_step),
    size(_size) {
  }

  virtual ~Vector() {
    if (own_array) {
      delete[] backing_array;
    }
  }

  RationalNumber& operator[](int j) {
    assert(0 <= j && j < size);
    return backing_array[j * step];
  };

private:
  RationalNumber* backing_array;
  bool own_array;
  int step;
  int size;
};

class Matrix {
public:
  const int height;
  const int width;

  Matrix(const Matrix& m) = delete;
  Matrix& operator =(Matrix &m) = delete;
  Matrix& operator =(const Matrix &m) = delete;

  Matrix(int _height, int _width): height(_height), width(_width) {
    elements = new RationalNumber[height * width];
  }

  // return i'th row as a vector
  Vector operator[](int i) {
    assert(0 <= i && i < height);
    return Vector(elements + width * i, false, 1, width);
  }

  virtual ~Matrix() {
    delete[] elements;
  }

  const RationalNumber& element_at(int i, int j) const {
    assert(0 <= i && i < height);
    assert(0 <= j && j < width);
    return elements[i * width + j];
  }

  void set_element_at(int i, int j, const RationalNumber& x) {
    assert(0 <= i && i < height);
    assert(0 <= j && j < width);
    elements[i * width + j] = x;
  }

private:
  RationalNumber* elements;

};

std::ostream& operator << (std::ostream& out, const Matrix& m) {
  for (int i = 0; i < m.height; ++i) {
    for (int j = 0; j < m.width; ++j) {
      out << m.element_at(i, j);
      if (j != m.width - 1) {
        out << " ";
      }
    }
    out << std::endl;
  }
  return out;
}
