
#ifndef _SHDRAWBUFFER_H
#define _SHDRAWBUFFER_H

#include "Base\ShVariable.h"

class ShDrawBuffer {

public:
	bool saveToBuffer;
	DrawType buffer;

	DrawType drawType;

	ShDrawBuffer();
	~ShDrawBuffer();

	
};

#endif //_SHDRAWBUFFER_H