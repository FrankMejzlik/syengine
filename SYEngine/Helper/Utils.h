#pragma once

#include <string>
#include <fstream>

#include "common.h"

namespace SYE
{

namespace Utils
{
  std::string ReadTextFile(std::string_view filepath)
  {
    std::string content;
    std::fstream file(filepath.data(), std::ios::in);

    // If opening file failed
    if (!file.is_open())
    {
      DLog(eLogType::cError, "Failed to open file %s.", filepath);
      return std::string();
    }

    // Init empty line
    std::string line("");

    while (!file.eof())
    {
      std::getline(file, line);
      content.append(line + '\n');
    }

    file.close();

    return content;
  }

} // namespace Utils

} // namespace SYE


