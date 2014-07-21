#ifndef __ANARCH_TEST_INVERSE_SCRATCH_HPP__
#define __ANARCH_TEST_INVERSE_SCRATCH_HPP__

#include "inverter.hpp"
#include "../../../src/arch/x64/vmm/scratch.hpp"
#include <anarch/api/panic>

namespace anarch {

namespace x64 {

Scratch::Scratch(uint64_t *) {  
}

void Scratch::CreateMappings(uint64_t *, Allocator &) {
}

bool Scratch::Alloc(VirtAddr & addr, PhysAddr page) {
  addr = InvertPhys(page);
  return true;
}

void Scratch::Reassign(VirtAddr, PhysAddr) {
  Panic("inverse scratch does not support Reassign()");
}

void Scratch::Free(VirtAddr) {
  
}

}

}

#endif
