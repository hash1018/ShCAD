

#ifndef _SHDRAFT_H
#define _SHDRAFT_H

#include "ShPoint.h"

class ShDraftFlag {
	friend class ShGraphicView;

private:
	bool acceptOrthogonal;
	bool acceptSnap;

public:
	ShDraftFlag() :acceptOrthogonal(false), acceptSnap(false) {}
	~ShDraftFlag() {}
	ShDraftFlag& operator=(const ShDraftFlag& other) {
		this->acceptOrthogonal = other.acceptOrthogonal;
		this->acceptSnap = other.acceptSnap;
		return *this;
	}

	inline bool AcceptOrthogonal() const { return this->acceptOrthogonal; }
	inline bool AcceptSnap() const { return this->acceptSnap; }
};

class ShAllowedDraftData {

private:
	bool allowOrthogonal;
	bool allowSnap;
	ShPoint3d snapBasePoint;
	ShPoint3d orthogonalBasePoint;

public:
	ShAllowedDraftData() : allowOrthogonal(false)
		, allowSnap(false) {}
	~ShAllowedDraftData() {}

	void SetAllowOrthogonal(bool on) { this->allowOrthogonal = on; }
	void SetAllowtSnap(bool on) { this->allowSnap = on; }
	void SetSnapBasePoint(const ShPoint3d& point) { this->snapBasePoint = point; }
	void SetOrthogonalBasePoint(const ShPoint3d& point) { this->orthogonalBasePoint = point; }

	inline bool AllowOrthogonal() const { return this->allowOrthogonal; }
	inline bool AllowSnap() const { return this->allowSnap; }
	inline ShPoint3d GetSnapBasePoint() const { return this->snapBasePoint; }
	inline ShPoint3d GetOrthogonalBasePoint() const { return this->orthogonalBasePoint; }
};

#endif //_SHDRAFT_H