#include "pic.hpp"
#include "../common.hpp"
#include <anarch/critical>
#include <anarch/stream>
#include <anarch/new>

namespace anarch {

namespace x64 {

namespace {

Pic gPic;

void IOWait() {
  OutB(0x80, 0);
}

const uint16_t PIC1_COMMAND = 0x20;
const uint16_t PIC1_DATA = 0x21;
const uint16_t PIC2_COMMAND = 0xa0;
const uint16_t PIC2_DATA = 0xa1;

const uint8_t ICW1_ICW4 = 0x01; /* ICW4 (not) needed */
const uint8_t ICW1_INIT = 0x10; /* Initialization - required! */
const uint8_t ICW4_8086 = 0x01; /* 8086/88 (MCS-80/85) mode */

}

void Pic::InitGlobal() {
  new(&gPic) Pic();
}

Pic & Pic::GetGlobal() {
  return gPic;
}

void Pic::Remap(uint8_t masterBase, uint8_t slaveBase, uint8_t masterMask,
                uint8_t slaveMask) {
  OutB(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
  IOWait();
  OutB(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);
  IOWait();
  OutB(PIC1_DATA, masterBase); // ICW2: Master PIC vector offset
  IOWait();
  OutB(PIC2_DATA, slaveBase); // ICW2: Slave PIC vector offset
  IOWait();
  OutB(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  IOWait();
  OutB(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
  IOWait();

  OutB(PIC1_DATA, ICW4_8086);
  IOWait();
  OutB(PIC2_DATA, ICW4_8086);
  IOWait();

  OutB(PIC1_DATA, masterMask);
  OutB(PIC2_DATA, slaveMask);
}

ansa::DepList Pic::GetDependencies() {
  return ansa::DepList(&StreamModule::GetGlobal());
}

void Pic::Initialize() {
  cout << "Initializing legacy PIC...";
  Remap(0xf0, 0xf8, 0xff, 0xff);
  cout << " [OK]" << endl;
}

}

}
