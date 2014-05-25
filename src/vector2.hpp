#pragma once

#include <cmath>

template <typename T>
class Vector2
{
public:
  T x, y;

  Vector2();
  Vector2(T x, T y) { Set(x, y); }
  Vector2(const Vector2<T> &vec) { Set(vec); }

  void Set(T x, T y);
  void Set(const Vector2<T> &vec) { Set(vec.x, vec.y); }

  /* Math stuff */
  float Magnitude()
  {
    return std::sqrtf((x *x) + (y * y));
  }

  Vector2<T> Normalized()
  {
    Vector2<T> normalized(x, y);

    float imag = 1.0f / Magnitude();
    normalized.x *= imag;
    normalized.y *= imag;

    return normalized;
  }

  void Normalize()
  {
    float imag = 1.0f / Magnitude();

    x *= imag;
    y *= imag;
  }

  float Dot(const Vector2<T> &other)
  {
    return (x * other.x) + (y * other.y);
  }
};

/* Operator overloading */
template <typename T>
Vector2<T> operator + (const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.x + right.x, left.y + right.y); }
template <typename T>
Vector2<T> operator + (const Vector2<T> &left, T right) { return Vector2<T>(left.x + right, left.y + right); }
template <typename T>
Vector2<T> operator - (const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.x - right.x, left.y - right.y); }
template <typename T>
Vector2<T> operator - (const Vector2<T> &left, T right) { return Vector2<T>(left.x - right, left.y - right); }
template <typename T>
Vector2<T> operator * (const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.x * right.x, left.y * right.y); }
template <typename T>
Vector2<T> operator * (const Vector2<T> &left, T right) { return Vector2<T>(left.x * right, left.y * right); }
template <typename T>
Vector2<T> operator / (const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.x / right.x, left.y / right.y); }
template <typename T>
Vector2<T> operator / (const Vector2<T> &left, T right) { return Vector2<T>(left.x / right, left.y / right); }

template <typename T>
Vector2<T> &operator += (Vector2<T> &left, const Vector2<T> &right) { left = left + right; return left; }
template <typename T>
Vector2<T> &operator -= (Vector2<T> &left, const Vector2<T> &right) { left = left - right; return left; }
template <typename T>
Vector2<T> &operator *= (Vector2<T> &left, const Vector2<T> &right) { left = left * right; return left; }
template <typename T>
Vector2<T> &operator /= (Vector2<T> &left, const Vector2<T> &right) { left = left / right; return left; }


template <typename T>
Vector2<T>::Vector2()
{
  x = y = 0;
}

template <typename T>
void Vector2<T>::Set(T x, T y)
{
  this->x = x;
  this->y = y;
}


/* Global typedefs */
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
