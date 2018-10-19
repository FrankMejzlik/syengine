#pragma once

#include <string>
#include <vector>

namespace WeSp {

enum class eCommandType
{
  Null,
  CreateBlock,
  CreateSphere,
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
  Command(eCommandType type, std::wstring stringData);
  Command(eCommandType type, std::vector<int> _intData);
  Command(eCommandType type, std::vector<float> _floatData);
  ~Command();
    
  eCommandType GetType() const;
  std::vector<float> GetFloatData() const;
  std::vector<int> GetIntData() const;

private:
  eCommandType _commandType;
  std::wstring _stringData;
  std::vector<int> _intData;
  std::vector<float> _floatData;

};

}