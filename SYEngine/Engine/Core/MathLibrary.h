#pragma once

/**
 * Abstraction layer over whatever math libraries we're currently using to preserve consistent API.
 *
 * Currently implementing GLM.
 */

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
  ~Vector3() noexcept = default;



  // Attributes
private:
  /** Implemented type */
  VectorType _vector;


protected:
private:

};


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
