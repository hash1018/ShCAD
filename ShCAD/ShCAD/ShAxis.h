

#ifndef _SHAXIS_H
#define _SHAXIS_H

#include "ShPoint.h"

class QPainter;
class ShGraphicView;
class ShAxis {

private:
	ShPoint3d center;

public:
	ShAxis();
	ShAxis(double centerX, double centerY);
	~ShAxis();
	ShAxis(const ShAxis& other);
	ShAxis& operator=(const ShAxis& other);

	void Draw(QPainter *painter, ShGraphicView *view);

	ShPoint3d& GetCenter();
	void SetCenter(const ShPoint3d& center);


};

inline ShPoint3d& ShAxis::GetCenter() {

	return this->center;
}

#endif //_SHAXIS_H