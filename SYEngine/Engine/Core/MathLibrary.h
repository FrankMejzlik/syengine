#pragma once

/**
 * Abstraction layer over whatever math libraries we're currently using to preserve consistent API.
 *
 * Currently implementing GLM.
 */
#define _USE_MATH_DEFINES
#include <math.h>


#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace SYE
{

/** 
 * Wrapper class implementing Vector data structure.
 */
template <typename VectorType, typename ElementType>
class Vector3
{
  // Methods
public:
  Vector3() {}
  Vector3(ElementType x, ElementType y, ElementType z):
    _vector(x, y, z)
  {}
  Vector3(const Vector3<VectorType, ElementType>& other) = default;
  Vector3(Vector3<VectorType, ElementType>&& other) = default;
  Vector3(const glm::vec3& other) :
    _vector(other)
  {}
  Vector3(glm::vec3&& other) :
    _vector(std::move(other))
  {}
  ~Vector3() noexcept = default;

  ElementType GetX() const { return _vector.x; }
  ElementType GetY() const { return _vector.y; }
  ElementType GetZ() const { return _vector.z; }

  void SetX(ElementType x) { _vector.x = x; };
  void SetY(ElementType y) { _vector.y = y; };
  void SetZ(ElementType z) { _vector.z = z; };

  const VectorType& GetData() const { return _vector; }


  Vector3<VectorType, ElementType>& operator=(const Vector3<VectorType, ElementType>& other) = default;
  Vector3<VectorType, ElementType>& operator=(Vector3<VectorType, ElementType>&& other) = default;
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

template <typename ElementType>
ElementType ToRadians(ElementType first)
{
  return glm::radians(first);
}


/**
* Typedefs
*/
#if USING_DOUBLES

// (double, double, double)
using Vector3f = Vector3<glm::dvec3, double>;

#else

// (float, float, float)
using Vector3f = Vector3<glm::vec3, float>;

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
