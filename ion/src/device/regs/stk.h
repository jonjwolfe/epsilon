#ifndef REGS_STK_H
#define REGS_STK_H

#include "register.h"

class STK {
public:
  class CTRL : public Register32 {
  public:
    REGS_BOOL_FIELD(ENABLE, 0);
    REGS_BOOL_FIELD(TICKINT, 1);
    REGS_BOOL_FIELD_R(CLKSOURCE, 2);
    REGS_BOOL_FIELD(COUNTFLAG, 16);
  };

  class LOAD : public Register32 {
  public:
  };

  class VAL : public Register32 {
  public:
  };

  class CALIB : public Register32 {
  public:

	REGS_BOOL_FIELD(SKEW, 30);
	REGS_BOOL_FIELD(NOREF, 0);

    int getTenMS() {
      return getBitRange(23, 0);
    }
    void setTenMS(int t) volatile {
      setBitRange(23, 0, (uint32_t)t);
    }
  };



  constexpr STK() {};
  REGS_REGISTER_AT(CTRL, 0x00);
  REGS_REGISTER_AT(LOAD, 0x04);
  REGS_REGISTER_AT(VAL, 0x08);
  REGS_REGISTER_AT(CALIB, 0x0C);

private:
  constexpr uint32_t Base() const {
    return 0xE000E010;
  }
};

constexpr STK STK;

#endif
