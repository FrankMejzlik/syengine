#pragma once

#include <iostream>

#include "MathLibrary.h"

using namespace SYE;

bool TEST_Matrix4()
{
  glm::mat4 m1;
  glm::mat4 m2;

  m1[0] = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
  m1[1] = glm::vec4(0.0f, 1.0f, 2.0f, 3.0f);
  m1[2] = glm::vec4(0.0f, 0.0f, 1.0f, 2.0f);
  m1[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

  std::cout << glm::to_string(m1) << std::endl;
  std::cout << "===" << std::endl;

  m2[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
  m2[1] = glm::vec4(2.0f, 1.0f, 0.0f, 0.0f);
  m2[2] = glm::vec4(3.0f, 2.0f, 1.0f, 0.0f);
  m2[3] = glm::vec4(4.0f, 3.0f, 2.0f, 1.0f);

  std::cout << glm::to_string(m2) << std::endl;
  std::cout << "===" << std::endl;

  glm::mat4 m3 = m1 * m2;
  std::cout << glm::to_string(m3) << std::endl;
  std::cout << "===" << std::endl;


  Matrix4f mm1;
  Matrix4f mm2;

  mm1.SetCol(0, Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
  mm1.SetCol(1, Vector4f(0.0f, 1.0f, 2.0f, 3.0f));
  mm1.SetCol(2, Vector4f(0.0f, 0.0f, 1.0f, 2.0f));
  mm1.SetCol(3, Vector4f(0.0f, 0.0f, 0.0f, 1.0f));

  std::cout << ToString(mm1) << std::endl;
  std::cout << "===" << std::endl;

  mm2.SetCol(0, Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
  mm2.SetCol(1, Vector4f(2.0f, 1.0f, 0.0f, 0.0f));
  mm2.SetCol(2, Vector4f(3.0f, 2.0f, 1.0f, 0.0f));
  mm2.SetCol(3, Vector4f(4.0f, 3.0f, 2.0f, 1.0f));


  std::cout << ToString(mm2) << std::endl;
  std::cout << "===" << std::endl;

  //  Chceck it
  assert(mm1.GetData() == m1);
  assert(mm2.GetData() == m2);

  Matrix4f mm3 = mm1 * mm2;
  std::cout << ToString(mm3) << std::endl;
  std::cout << "===" << std::endl;

  assert(mm3.GetData() == m3);


  return true;

}


bool TEST_MathLibrary()
{
  bool result = TEST_Matrix4();

  return result;
}