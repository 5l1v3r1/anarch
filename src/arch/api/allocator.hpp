#ifndef __ANARCH_API_ALLOCATOR_HPP__
#define __ANARCH_API_ALLOCATOR_HPP__

#include <anarch/types>
#include <ansa/nocopy>

namespace anarch {

class Allocator : public ansa::NoCopy {
public:
  /**
   * Allocate aligned physical memory.
   * @noncritical
   */
  virtual bool Alloc(PhysAddr & result, PhysSize size, PhysSize align) = 0;
  
  /**
   * Free physical memory.
   * @noncritical
   */
  virtual void Free(PhysAddr address) = 0;
  
  /**
   * Returns `false` if `address` could not have been allocated by this
   * physical allocator
   * @noncritical
   */
  virtual bool Owns(PhysAddr address) = 0;
  
  /**
   * Get the amount of physical memory in use by the system.
   * @noncritical
   */
  virtual PhysSize Used() = 0;
  
  /**
   * Get the amount of unused physical memory available to the system.
   * @noncritical
   */
  virtual PhysSize Available() = 0;
  
  /**
   * Get the amount of total physical memory on the system.
   * @noncritical
   */
  virtual PhysSize Total() = 0;
  
  /**
   * Allocate physical memory and map it into contiguous virtual memory.
   */
  virtual bool AllocAndMap(VirtAddr &, PhysSize, bool bigPages = true);
  
  /**
   * Do the inverse of AllocAndMap(). This method looks up each page, unmaps
   * it, frees it, and moves on to the next one.
   */
  virtual void FreeAndUnmap(VirtAddr addr, PhysSize size);
  
  /**
   * Attempt to allocate a contiguous buffer of pages and map it into the
   * global address space.
   */
  virtual bool AllocAndMapContiguous(VirtAddr &, PhysSize,
                                     bool bigPages = true);
  
  /**
   * Attempt to free a contiguous buffer of pages and unmap it from the global
   * address space.
   */
  virtual void FreeAndUnmapContiguous(VirtAddr, PhysSize);
};

}

#endif
