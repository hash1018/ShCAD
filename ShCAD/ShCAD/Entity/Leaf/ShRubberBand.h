
#ifndef _SHRUBBERBAND_H
#define _SHRUBBERBAND_H

#include "ShLine.h"

class ShRubberBand : public ShLine {

private:
	ShLine *line;

public:
	ShRubberBand();
	ShRubberBand(const ShRubberBand &other);
	~ShRubberBand();

	virtual ShRubberBand* clone();
	virtual void accept(ShVisitor *visitor);

	virtual void setData(const ShLineData &data);
	virtual void setEnd(const ShPoint3d &end);
	virtual ShLineData getData();
	virtual ShPoint3d getStart();
	virtual ShPoint3d getEnd();

	void clear();
	void create(const ShLineData &data);
	bool isExist();

};

#endif //_SHRUBBERBAND_H