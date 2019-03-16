#pragma once

#include <map>
#include <vector>

#include "BaseModule.h"
#include "Shader.h"

using namespace SYE;

namespace SYE 
{

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
  
  bool InitializeScene(Scene* pScene);


  void ClearShaders();

  NewShader* CreateShader(
    std::vector<NewShader::eUniforms> _requiredUniforms,
    std::vector<NewShader::eUniforms> _optionalUniforms,
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath  = std::string_view(),
    std::string_view gsFilepath  = std::string_view()
  );

  NewShader* GetStandardShader() const;
  NewShader* GetStandardOrthoShadowMapShader() const;
  NewShader* GetStandardPerspectiveShadowMapShader() const;

private:
  bool LoadStandardShaders();

  // Attributes
private:
  //! List of active Shader mapped by their GUID
  std::map< size_t, std::unique_ptr<NewShader> > _shaders;

  //! System Shaders
  std::vector<NewShader*> _systemShaders;
};

}