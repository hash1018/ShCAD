
#ifndef _SHAVAILABLEDRAFT_H
#define _SHAVAILABLEDRAFT_H

#include "ShPoint3d.h"


class ShAvailableDraft {

private:
	bool availableOrthogonal;
	ShPoint3d orthogonalBasePoint;

	bool availableSnap;
	ShPoint3d snapBasePoint;
	
public:
	ShAvailableDraft();
	~ShAvailableDraft();

	ShAvailableDraft& operator=(const ShAvailableDraft &other);

	void setAvailableOrthogonal(bool on) { this->availableOrthogonal = on; }
	void setOrthogonalBasePoint(const ShPoint3d &point) { this->orthogonalBasePoint = point; }
	void setAvailableSnap(bool on) { this->availableSnap = on; }
	void setSnapBasePoint(const ShPoint3d &point) { this->snapBasePoint = point; }
	
	inline bool getAvailableOrthogonal() const { return this->availableOrthogonal; }
	inline ShPoint3d getOrthogonalBasePoint() const { return this->orthogonalBasePoint; }
	inline bool getAvailableSnap() const { return this->availableSnap; }
	inline ShPoint3d getSnapBasePoint() const { return this->snapBasePoint; }

};

#endif //_SHAVAILABLEDRAFT_H