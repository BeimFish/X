

#include "res\other\address\arm_address.h"//提供Core_Base地址


#include"res\static\arm\cm_id.h"

ID::ID()
{
	id=((ID_Type*)(CM_CORE_BASE + 0x0D00UL));
}

_u32 ID::getArcthitecturn()
{
	return (id->CPUID >> 24) & 0x000000ff;
	//Implementer[24,8]
}
_u32 ID::getPartno()
{
	return (id->CPUID >> 4) & 0x00000fff;
	//Partno[4,12]]
}



