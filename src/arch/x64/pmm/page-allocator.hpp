#ifndef __X64_PAGE_ALLOCATOR_HPP__
#define __X64_PAGE_ALLOCATOR_HPP__

#include <arch-specific/types.hpp>

namespace OS {

namespace x64 {

class PageAllocator {
public:
  virtual PhysAddr AllocPage() = 0;
  virtual void FreePage(PhysAddr p) = 0;
};

}

}

#endif
