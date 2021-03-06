#include <anarch/malloc>
#include <ansa/module>
#include <ansa/macros>

namespace anarch {

namespace x64 {

class GlobalMalloc : public ansa::Module {
public:
  static void InitGlobal();
  static GlobalMalloc & GetGlobal();
  
  VirtualAllocator & GetAllocator();
  
protected:
  virtual ansa::DepList GetDependencies();
  virtual void Initialize();
  
private:
  char mallocBuf[sizeof(Malloc)] ANSA_ALIGNED(8);
};

}

}
