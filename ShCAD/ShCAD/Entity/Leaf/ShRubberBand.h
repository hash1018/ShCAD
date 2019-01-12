

#ifndef _SHRUBBERBAND_H
#define _SHRUBBERBAND_H

#include "ShLine.h"

class ShRubberBand : public ShLine {

public:
	ShRubberBand();
	ShRubberBand(const ShLineData &data);
	ShRubberBand(const ShRubberBand& other);
	ShRubberBand& operator=(const ShRubberBand& other);
	~ShRubberBand();

	ShRubberBand* Clone();
	virtual void Accept(ShVisitor *shVisitor);

	


};


#endif //_SHRUBBERBAND_H