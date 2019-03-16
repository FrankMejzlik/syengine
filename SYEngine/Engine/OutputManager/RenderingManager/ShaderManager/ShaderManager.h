#pragma once

#include <map>

#include "BaseModule.h"

using namespace SYE;

namespace SYE 
{

class NewShader;


class ShaderManager :
  public BaseModule
{
public:
  ShaderManager() = delete;

  ShaderManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~ShaderManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;
  virtual void TerminateGame() override;

  void ClearShaders();

  NewShader* CreateShader(
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath  = std::string_view(),
    std::string_view gsFilepath  = std::string_view()
  );

private:
  //! List of active Shader mapped by their GUID
  std::map< size_t, std::unique_ptr<NewShader> > _shaders;
};

}