
#include "Command.h"

using namespace WeSp;

Command::Command(eCommandType type):
  _commandType(type), _stringData(L""), _intData(0), _floatData(0.0f)
{}

Command::Command(eCommandType type, std::wstring stringData) :
  _commandType(type), _stringData(stringData), _intData(0), _floatData(0.0f)
{}

Command::Command(eCommandType type, std::vector<int> _intData):
  _commandType(type), _intData(_intData), _stringData(L""), _floatData(0.0f)
{}

Command::Command(eCommandType type, std::vector<float> _floatData) :
  _commandType(type), _intData(0), _stringData(L""), _floatData(_floatData)
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

std::vector<int> Command::GetIntData() const
{
  return _intData;
}
