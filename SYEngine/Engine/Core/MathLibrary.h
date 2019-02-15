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

using Vector3f = Vector<glm::vec3>;
using Vector3i = Vector<glm::ivec3>;
using Vector3u = Vector<glm::uvec3>;

using Vector2f = Vector<glm::vec2>;
using Vector2i = Vector<glm::ivec2>;
using Vector2u = Vector<glm::uvec2>;

template <typename ValueType>
class Vector
{
public:
  MathLibrary() = delete;
  ~MathLibrary() noexcept = default;

private:
  ValueType _vector;

};


} // SYE
