

#ifndef _SHRUBBERBAND_H
#define _SHRUBBERBAND_H

#include "ShVector.h"
class QPainter;
class ShRubberBand {

private:
	ShVector start;
	ShVector end;

public:
	ShRubberBand(const ShVector& start, const ShVector& end);
	~ShRubberBand();

	double GetStartX() const;
	double GetStartY() const;
	double GetEndX() const;
	double GetEndY() const;
	ShVector& GetStart();
	ShVector& GetEnd();

	void SetStartX(double startX);
	void SetStartY(double startY);
	void SetEndX(double endX);
	void SetEndY(double endY);

	

};

inline double ShRubberBand::GetStartX() const {

	return this->start.x;
}

inline double ShRubberBand::GetStartY() const {

	return this->start.y;
}

inline double ShRubberBand::GetEndX() const {

	return this->end.x;
}

inline double ShRubberBand::GetEndY() const {

	return this->end.y;
}

inline ShVector& ShRubberBand::GetStart() {

	return this->start;
}

inline ShVector& ShRubberBand::GetEnd() {

	return this->end;
}

#endif //_SHRUBBERBAND_H