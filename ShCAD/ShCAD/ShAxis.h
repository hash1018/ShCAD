

#ifndef _SHAXIS_H
#define _SHAXIS_H

#include "ShVector.h"

class QPainter;
class ShGraphicView;
class ShAxis {

private:
	ShVector center;

public:
	ShAxis();
	ShAxis(double centerX, double centerY);
	~ShAxis();
	ShAxis(const ShAxis& other);
	ShAxis& operator=(const ShAxis& other);

	void Draw(QPainter *painter, ShGraphicView *view);

	ShVector& GetCenter();
	void SetCenter(const ShVector& center);


};

inline ShVector& ShAxis::GetCenter() {

	return this->center;
}

#endif //_SHAXIS_H