#pragma once

/**
 * Abstraction layer over whatever math libraries we're currently using to preserve consistent API.
 *
 * Currently implementing GLM.
 */
#define _USE_MATH_DEFINES
#include <math.h>

#pragma warning(push, 1)
#include "LinearMath/btVector3.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <GLM/gtx/string_cast.hpp>
#pragma warning(pop)

namespace SYE
{


template <typename ElementType>
ElementType ToRadians(ElementType first)
{
  return glm::radians(first);
}

/**
 * Wrapper class implementing Vector3 data structure.
 */
template <typename VectorType, typename ElementType>
class Vector3
{
public:

  // Methods
public:
  Vector3() {}
  Vector3(ElementType x, ElementType y, ElementType z) :
    _vector(x, y, z)
  {}
  Vector3(const Vector3<VectorType, ElementType>& other) = default;
  Vector3(Vector3<VectorType, ElementType>&& other) = default;
  // Vector3(const glm::vec3&)
  Vector3(const glm::vec3& other) :
    _vector(other)
  {};
  // Vector3(glm::vec3&&)
  Vector3(glm::vec3&& other) :
    _vector(std::move(other))
  {};
  // Vector3(const btVector3&)
  Vector3(const btVector3& other) :
    _vector(other.x(), other.y(), other.z())
  {};
  ~Vector3() noexcept = default;

  // Implicit conversion Vector3 -> btVector3
  operator btVector3() const { return btVector3(_vector.x, _vector.y, _vector.z); }

  // Asignment operator
  Vector3<VectorType, ElementType>& operator=(const Vector3<VectorType, ElementType>& other) = default;
  // Move asignment operator
  Vector3<VectorType, ElementType>& operator=(Vector3<VectorType, ElementType>&& other) = default;

  ElementType GetX() const { return _vector.x; }
  ElementType GetY() const { return _vector.y; }
  ElementType GetZ() const { return _vector.z; }

  void SetX(ElementType x) { _vector.x = x; };
  void SetY(ElementType y) { _vector.y = y; };
  void SetZ(ElementType z) { _vector.z = z; };

  const VectorType& GetData() const { return _vector; }

  // Vector3 = btVector3
  Vector3<VectorType, ElementType>& operator=(const btVector3& other)
  {
    _vector.x = other.x();
    _vector.y = other.y();
    _vector.z = other.z();

    return *this;
  }

  // Vector3 = glm::vec3
  Vector3<VectorType, ElementType>& operator=(const glm::vec3& other)
  {
    _vector.x = other.x();
    _vector.y = other.y();
    _vector.z = other.z();

    return *this;
  }

  Vector3<VectorType, ElementType> operator*(ElementType other) const
  {
    return Vector3<VectorType, ElementType>(_vector * other);
  }

  Vector3<VectorType, ElementType> operator+(const Vector3<VectorType, ElementType>& other) const
  {
    return Vector3<VectorType, ElementType>(_vector + other.GetData());
  }

  Vector3<VectorType, ElementType> operator+=(const Vector3<VectorType, ElementType>& other) const
  {
    return Vector3<VectorType, ElementType>(_vector + other.GetData());
  }

  Vector3<VectorType, ElementType> operator-(const Vector3<VectorType, ElementType>& other) const
  {
    return Vector3<VectorType, ElementType>(_vector - other.GetData());
  }
  Vector3<VectorType, ElementType> operator-=(const Vector3<VectorType, ElementType>& other) const
  {
    return Vector3<VectorType, ElementType>(_vector - other.GetData());
  }


  // Attributes
private:
  /** Implemented type */
  VectorType _vector;


protected:
private:

};

template <typename VectorType, typename ElementType>
Vector3<VectorType, ElementType> Normalize(const Vector3<VectorType, ElementType>& first)
{
  return Vector3<VectorType, ElementType>(glm::normalize(first.GetData()));
}

template <typename VectorType, typename ElementType>
Vector3<VectorType, ElementType> Cross(const Vector3<VectorType, ElementType>& first, const Vector3<VectorType, ElementType>& second)
{
  return Vector3<VectorType, ElementType>(glm::cross(first.GetData(), second.GetData()));
}


/*!
 * Wrapper class implementing Vector4 data structure
 */
template <typename VectorType, typename ElementType>
class Vector4
{
public:

  // Methods
public:
  Vector4() {}
  Vector4(ElementType x, ElementType y, ElementType z, ElementType w) :
    _vector(x, y, z, w)
  {}
  Vector4(const Vector4<VectorType, ElementType>& other) = default;
  Vector4(Vector4<VectorType, ElementType>&& other) = default;
  // Vector4(const glm::vec4&)
  Vector4(const glm::vec4& other) :
    _vector(other)
  {};
  // Vector4(glm::vec4&&)
  Vector4(glm::vec4&& other) :
    _vector(std::move(other))
  {};
  // Vector4(const btVector4&)
  Vector4(const btVector4& other) :
    _vector(other.x(), other.y(), other.z())
  {};
  ~Vector4() noexcept = default;

  // Implicit conversion Vector4 -> btVector4
  operator btVector4() const { return btVector4(_vector.x, _vector.y, _vector.z); }

  // Asignment operator
  Vector4<VectorType, ElementType>& operator=(const Vector4<VectorType, ElementType>& other) = default;
  // Move asignment operator
  Vector4<VectorType, ElementType>& operator=(Vector4<VectorType, ElementType>&& other) = default;

  ElementType GetX() const { return _vector.x; }
  ElementType GetY() const { return _vector.y; }
  ElementType GetZ() const { return _vector.z; }

  void SetX(ElementType x) { _vector.x = x; };
  void SetY(ElementType y) { _vector.y = y; };
  void SetZ(ElementType z) { _vector.z = z; };

  const VectorType& GetData() const { return _vector; }

  // Vector4 = btVector4
  Vector4<VectorType, ElementType>& operator=(const btVector4& other)
  {
    _vector.x = other.x();
    _vector.y = other.y();
    _vector.z = other.z();

    return *this;
  }

  // Vector4 = glm::vec4
  Vector4<VectorType, ElementType>& operator=(const glm::vec4& other)
  {
    _vector = other;

    return *this;
  }

  Vector4<VectorType, ElementType> operator*(ElementType other) const
  {
    return Vector4<VectorType, ElementType>(_vector * other);
  }

  Vector4<VectorType, ElementType> operator+(const Vector4<VectorType, ElementType>& other) const
  {
    return Vector4<VectorType, ElementType>(_vector + other.GetData());
  }

  Vector4<VectorType, ElementType> operator+=(const Vector4<VectorType, ElementType>& other) const
  {
    return Vector4<VectorType, ElementType>(_vector + other.GetData());
  }

  Vector4<VectorType, ElementType> operator-(const Vector4<VectorType, ElementType>& other) const
  {
    return Vector4<VectorType, ElementType>(_vector - other.GetData());
  }
  Vector4<VectorType, ElementType> operator-=(const Vector4<VectorType, ElementType>& other) const
  {
    return Vector4<VectorType, ElementType>(_vector - other.GetData());
  }


  // Attributes
private:
  /** Implemented type */
  VectorType _vector;


protected:
private:

};

template <typename VectorType, typename ElementType>
Vector4<VectorType, ElementType> Normalize(const Vector4<VectorType, ElementType>& first)
{
  return Vector4<VectorType, ElementType>(glm::normalize(first.GetData()));
}

template <typename VectorType, typename ElementType>
Vector4<VectorType, ElementType> Cross(const Vector4<VectorType, ElementType>& first, const Vector4<VectorType, ElementType>& second)
{
  return Vector4<VectorType, ElementType>(glm::cross(first.GetData(), second.GetData()));
}

/*!
 * Wrapper class implementing Matrix4 data structure
 */
template <typename MatrixType, typename ElementType>
class Matrix4
{
public:
  using ColumnType = Vector4<typename MatrixType::col_type, ElementType>;
  using LengthType = typename MatrixType::length_type;

  // Methods
public:
  Matrix4() = default;
  Matrix4(
    ElementType const& x0, ElementType const& y0, ElementType const& z0, ElementType const& w0,
    ElementType const& x1, ElementType const& y1, ElementType const& z1, ElementType const& w1,
    ElementType const& x2, ElementType const& y2, ElementType const& z2, ElementType const& w2,
    ElementType const& x3, ElementType const& y3, ElementType const& z3, ElementType const& w3
  ) :
    // Construct implemented matrix
    _matrix(
      x0, y0, z0, w0,
      x1, y1, z1, w1,
      x2, y2, z2, w2,
      x3, y3, z3, w3
    )
  {}
  Matrix4(const Matrix4<MatrixType, ElementType>& other) = default;
  Matrix4(Matrix4<MatrixType, ElementType>&& other) = default;
  ~Matrix4() noexcept = default;


  // Matrix4(const glm::mat4&)
  Matrix4(const glm::mat4& other) :
    _matrix(other)
  {};

  // Matrix4(glm::mat4&&)
  Matrix4(glm::mat4&& other) :
    _matrix(std::move(other))
  {};


  // Implicit conversion Matrix4 -> glm::mat4
  operator glm::mat4() const { return _matrix; }

  // Asignment operator
  Matrix4<MatrixType, ElementType>& operator=(const Matrix4<MatrixType, ElementType>& other) = default;

  // Move asignment operator
  Matrix4<MatrixType, ElementType>& operator=(Matrix4<MatrixType, ElementType>&& other) = default;

  ColumnType GetCol(size_t i) const { return _matrix[i]; }

  void SetCol(size_t i, Vector4<typename MatrixType::col_type, ElementType> col) { _matrix[static_cast<LengthType>(i)] = col.GetData(); };

  const MatrixType& GetData() const { return _matrix; }

  // Matrix4 = glm::vec3
  Matrix4<MatrixType, ElementType>& operator=(const glm::mat4& other)
  {
    _matrix = other;

    return *this;
  }

  Matrix4<MatrixType, ElementType> operator*(ElementType other) const
  {
    return Matrix4<MatrixType, ElementType>(_matrix * other);
  }

  Matrix4<MatrixType, ElementType> operator*(const Matrix4<MatrixType, ElementType>& other) const
  {
    return Matrix4<MatrixType, ElementType>(_matrix * other.GetData());
  }


  // Attributes
private:
  //! Implemented matrix type
  MatrixType _matrix;

};

template <typename Type>
std::string ToString(Type const& x)
{
  return glm::to_string(x.GetData());
}

/**
* Typedefs
*/
#if USING_DOUBLES

// (double, double, double)
using Vector3f = Vector3<glm::dvec3, double>;

#else

//! (float, float, float)
using Vector3f = Vector3<glm::vec3, float>;
//! (float, float, float, float)
using Vector4f = Vector4<glm::vec4, float>;

//! 4x4 float matrix
using Matrix4f = Matrix4<glm::mat4, float>;

#endif
// (int, int, int)
using Vector3i = Vector3<glm::ivec3, int>;
// (uint, uint, uint)
using Vector3u = Vector3<glm::uvec3, unsigned int>;

//// (float, float)
//using Vector2f = Vector2<glm::vec2>;
//// (int, int)
//using Vector2i = Vector2<glm::ivec2>;
//// (uint, uint)
//using Vector2u = Vector2<glm::uvec2>;


} // SYE
