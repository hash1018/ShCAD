


#ifndef _SHLINE_H
#define _SHLINE_H

#include "ShLeaf.h"
#include "ShPoint.h"

class ShLineData {

public:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShLineData();
	ShLineData(const ShPoint3d& start, const ShPoint3d& end);
	ShLineData(const ShLineData& data);
	bool operator==(const ShLineData& data);
	ShLineData& operator=(const ShLineData &data);

};

/* Class for Line entity */


class ShLine : public ShLeaf {

protected:
	ShLineData data;

public:
	ShLine();
	ShLine(const ShLineData &data);
	ShLine(const ShPropertyData& propertyData, const ShLineData &data, ShLayer *layer);
	ShLine(const ShLine& other);
	ShLine& operator=(const ShLine& other);
	~ShLine();

	ShLine* Clone();
	virtual void Accept(ShVisitor *shVisitor);
	virtual void GetHitPoint(HitPoint hitPoint, ShPoint3d &point);

	ShLineData& GetData() const;
	void SetData(const ShLineData& data);

	ShPoint3d GetMid();
	inline ShPoint3d GetStart() const { return this->data.start; }
	inline ShPoint3d GetEnd() const { return this->data.end; }
	void SetStart(const ShPoint3d& start) { this->data.start = start; }
	void SetEnd(const ShPoint3d& end) { this->data.end = end; }
	

};

inline ShLineData& ShLine::GetData() const {

	return const_cast<ShLineData&>(this->data);
}

#endif //_SHLINE_H