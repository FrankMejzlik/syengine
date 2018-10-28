#pragma once


#include <map>

#include "BaseModule.h"
#include "Material.h"


using namespace WeSp;

namespace WeSp 
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

  std::shared_ptr<Material> GetDefaultMaterial() const;


private:
  std::map<std::string, std::shared_ptr<Material>> _genericMaterials;
};

}