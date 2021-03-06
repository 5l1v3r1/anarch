#ifndef __ANARCH_X64_MAP_SETUP_HPP__
#define __ANARCH_X64_MAP_SETUP_HPP__

#include "free-finder.hpp"
#include "../page-table.hpp"
#include "../../pmm/buddy-allocator.hpp"
#include "../../pmm/step-allocator.hpp"
#include <ansa/nocopy>

namespace anarch {

namespace x64 {

/**
 * Configure the GlobalMap nice and easy
 */
class MapSetup : public ansa::NoCopy {
public:
  MapSetup();
  
  void GenerateMap();
  void GeneratePageTable();
  void GenerateFreeFinder();
  void GenerateBuddyAllocator();
  
  PageTable * GetPageTable();
  FreeFinder * GetFreeFinder();
  BuddyAllocator * GetBuddyAllocator();
  
  PhysAddr GetPdpt();
  
private:
  PhysAddr kernelEnd;
  PhysAddr reservedEnd;
  StepAllocator stepAllocator;
  
  PhysAddr pdpt, pml4;
  int pdtOffset = 0;
  int pdptOffset = 0;
  PhysAddr currentPDT = 0;
  VirtAddr firstUnmapped = 0;
   
  void MapNext(size_t & linearSize);
};

}

}

#endif
