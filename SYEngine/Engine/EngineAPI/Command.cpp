
#include "Command.h"

using namespace SYE;

Command::Command(eCommandType type):
  _commandType(type), _stringData(), _intData(0), _floatData(0.0f)
{}

Command::Command(eCommandType type, std::vector<std::string> stringData) :
  _commandType(type), _stringData(stringData), _intData(0), _floatData(0.0f)
{
}

Command::Command(eCommandType type, std::vector<float> _floatData, std::vector<std::string> stringData):
  _commandType(type), _stringData(stringData), _intData(0), _floatData(_floatData)
{

}

Command::Command(eCommandType type, std::vector<uint64_t> _intData):
  _commandType(type), _intData(_intData), _stringData(), _floatData(0.0f)
{}

Command::Command(eCommandType type, std::vector<float> _floatData) :
  _commandType(type), _intData(0), _stringData(), _floatData(_floatData)
{}



Command::~Command()
{}

eCommandType Command::GetType() const
{
  return _commandType;
}

std::vector<float> Command::GetFloatData() const
{
  return _floatData;
}

std::vector<std::string> Command::GetStringData() const
{
  return _stringData;
}

std::vector<uint64_t> Command::GetUIntData() const
{
  return _intData;
}
