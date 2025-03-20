#include "core.h"
#include "res/other/instruction.h"
#ifdef USE_CM
#include"res/static/arm/cm_id.h"
#endif


Core& Core::init()
{
#ifdef USE_CM
	id = new ID;
#endif
	this->Arcthitecturn = id->getArcthitecturn();
	this->Partno = id->getPartno();
	return *this;
}
