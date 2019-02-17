#pragma once


#include <map>

#include "BaseModule.h"
#include "Material.h"


using namespace SYE;

namespace SYE 
{

class MaterialManager :
  public BaseModule
{
public:
  MaterialManager() = delete;

  MaterialManager(BaseModule &parentModule);
  ~MaterialManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<_Material> GetDefaultMaterial() const;


private:
  std::map<std::string, std::shared_ptr<_Material>> _genericMaterials;
};

}