
#ifndef CM_ID_H
#define CM_ID_H

#include"res/other/type.h"//提供基础类型支持
typedef struct
{
  volatile  _u32 CPUID;
            _u32 RESERVED0[5U];
            _u8  RESERVED1[12U];
            _u32 RESERVED2[7U];
  volatile  _u32 PFR[2U];
  volatile  _u32 DFR;
  volatile  _u32 ADR;
  volatile  _u32 MMFR[4U];
  volatile  _u32 ISAR[5U];
  }ID_Type;




class ID
{
	  ID_Type* id;
public:
	  ID();
	virtual _u32 getArcthitecturn();
	virtual _u32 getPartno();
};





#endif
