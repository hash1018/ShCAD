
#ifndef _SHLASTBASEPOINT_H
#define _SHLASTBASEPOINT_H

#include "Data\ShPoint3d.h"

#define shLastBasePoint ShLastBasePoint::getInstance()

class ShLastBasePoint {

private:
	ShPoint3d point;

private:
	ShLastBasePoint();
	~ShLastBasePoint();

	static ShLastBasePoint instance;

public:
	static ShLastBasePoint* getInstance();

	void setPoint(const ShPoint3d &point) { this->point = point; }
	
	inline const ShPoint3d& getPoint() const { return this->point; }

};

#endif //_SHLASTBASEPOINT_H