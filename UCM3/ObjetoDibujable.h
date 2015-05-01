#ifndef ObjetoDibujable_H_
#define ObjetoDibujable_H_

#include "Vector3.h"
#include "TAfin.h"

class ObjetoDibujable{
	protected:   
		TAfin* matriz;
	public:	
		virtual void dibuja()=0;
};

#endif