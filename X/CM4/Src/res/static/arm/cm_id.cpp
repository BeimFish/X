

#include "res\other\address\arm_address.h"
#define _ID  ((ID_Type*)(CM_CORE_BASE + 0x0D00UL))

#include"res\static\arm\cm_id.h"
_u32 ID::getArcthitecturn()
{
	return (_ID->CPUID >> 24) & 0x000000ff;
	//Implementer[24,8]
}
_u32 ID::getPartno()
{
	return (_ID->CPUID >> 4) & 0x00000fff;
	//Partno[4,12]]
}

#undef _ID

