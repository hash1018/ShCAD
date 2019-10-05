
#ifndef _SHLASTBASEPOINT_H
#define _SHLASTBASEPOINT_H

#include "Data\ShPoint3d.h"

class ShLastBasePoint {

private:
	ShPoint3d point;

public:
	ShLastBasePoint();
	~ShLastBasePoint();

public:
	void setPoint(const ShPoint3d &point) { this->point = point; }
	inline const ShPoint3d& getPoint() const { return this->point; }

};

#endif //_SHLASTBASEPOINT_H