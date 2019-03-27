
#ifndef _SHENTITYDATA_H
#define _SHENTITYDATA_H

#include "ShPoint.h"
class ShEntityData {

public:
	ShEntityData() {}
	ShEntityData(const ShEntityData& other) {}
	virtual ~ShEntityData() = 0 {}
	ShEntityData& operator=(const ShEntityData& other) { return *this; }
	virtual ShEntityData* Clone() = 0;
};

////////////////////////////////////////////////////////////////

class ShLineData : public ShEntityData {

public:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShLineData();
	ShLineData(const ShPoint3d& start, const ShPoint3d& end);
	ShLineData(const ShLineData& data);
	bool operator==(const ShLineData& data);
	ShLineData& operator=(const ShLineData &data);
	virtual ShLineData* Clone();

};

///////////////////////////////////////////////////////////////////

class ShCircleData : public ShEntityData {

public:
	ShPoint3d center;
	double radius;

	ShCircleData();
	ShCircleData(ShPoint3d& center, double radius);
	ShCircleData(const ShCircleData& data);
	bool operator==(const ShCircleData& data);
	ShCircleData& operator=(const ShCircleData &data);
	virtual ShCircleData* Clone();

};

//////////////////////////////////////////////////////////////////

class ShArcData : public ShEntityData {

public:
	ShPoint3d center;
	double radius;
	double startAngle;
	double endAngle;


	ShArcData();
	ShArcData(ShPoint3d& center, double radius, double startAngle, double endAngle);
	ShArcData(const ShArcData& data);
	bool operator==(const ShArcData& data);
	ShArcData& operator=(const ShArcData &data);
	virtual ShArcData* Clone();

};

//////////////////////////////////////////////////////////////////////

class ShPolyLineData : public ShEntityData {

public:
	

	ShPoint3d start;
	ShPoint3d end;

public:
	ShPolyLineData();
	ShPolyLineData(const ShPolyLineData& data);
	~ShPolyLineData();
	ShPolyLineData& operator=(const ShPolyLineData& data);
	virtual ShPolyLineData* Clone();
};

#endif //_SHENTITYDATA_H