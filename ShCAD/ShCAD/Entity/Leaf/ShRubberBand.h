
#ifndef _SHRUBBERBAND_H
#define _SHRUBBERBAND_H

#include "ShLine.h"

class ShRubberBand : public ShLine {

public:
	ShRubberBand();
	ShRubberBand(const ShLineData &data);
	ShRubberBand(const ShRubberBand &other);
	~ShRubberBand();

	ShRubberBand& operator=(const ShRubberBand &other);

	virtual ShRubberBand* clone();
	virtual void accept(ShVisitor *visitor);


};

#endif //_SHRUBBERBAND_H