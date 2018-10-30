#pragma once

#include <string>
#include <vector>

namespace SYE {

enum class eCommandType
{
  Null,
  CreateBlock,
  CreateSphere,
  CreateStaticModelFromFile,
  CreatedStaticModelFromFile,
  CreatePointLight,
  CreateSpotLight,
  CreatedObjectId,
  DeleteObjectId,
  DeletedObjectId,

  Terminate
};

enum class eCommandSubType
{  
  Null,
  Block, 
};

class Command
{
public:
  Command(eCommandType type);
  Command(eCommandType type, std::vector<std::string> stringData);
  Command(eCommandType type, std::vector<float> _floatData, std::vector<std::string> stringData);
  Command(eCommandType type, std::vector<uint64_t> _intData);
  Command(eCommandType type, std::vector<float> _floatData);
  ~Command();
    
  eCommandType GetType() const;
  std::vector<float> GetFloatData() const;
  std::vector<uint64_t> GetUIntData() const;
  std::vector<std::string> GetStringData() const;

private:
  eCommandType _commandType;
  std::vector<std::string> _stringData;
  std::vector<uint64_t> _intData;
  std::vector<float> _floatData;

};

}