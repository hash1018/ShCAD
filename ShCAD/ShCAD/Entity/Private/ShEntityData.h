

#ifndef _SHENTITYDATA_H
#define _SHENTITYDATA_H

#include "Data\ShPoint3d.h"

class ShEntityData {

public:
	ShEntityData();
	ShEntityData(const ShEntityData &other);
	virtual ~ShEntityData() = 0;

	ShEntityData& operator=(const ShEntityData &other);

};

class ShLineData : public ShEntityData {

public:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShLineData();
	ShLineData(const ShPoint3d &start, const ShPoint3d &end);
	ShLineData(const ShLineData &other);
	~ShLineData();

	ShLineData& operator=(const ShLineData &other);

};

class ShCircleData : public ShEntityData {

public:
	ShPoint3d center;
	double radius;

public:
	ShCircleData();
	ShCircleData(const ShPoint3d &center, double radius);
	ShCircleData(const ShCircleData &other);
	~ShCircleData();

	ShCircleData& operator=(const ShCircleData &other);

};

class ShArcData : public ShEntityData {

public:
	ShPoint3d center;
	double radius;
	double startAngle;
	double endAngle;

public:
	ShArcData();
	ShArcData(const ShPoint3d &center, double radius, double startAngle, double endAngle);
	ShArcData(const ShArcData &other);
	~ShArcData();

	ShArcData& operator=(const ShArcData &other);
};

class ShDimLinearData : public ShEntityData {

public:
	ShPoint3d firstOrigin;
	ShPoint3d secondOrigin;
	ShPoint3d firstDim;
	ShPoint3d secondDim;
	ShPoint3d text;

public:
	ShDimLinearData();
	ShDimLinearData(const ShPoint3d &firstOrigin, const ShPoint3d &secondOrigin, const ShPoint3d &firstDim, const ShPoint3d &secondDim,
		const ShPoint3d &text);
	ShDimLinearData(const ShDimLinearData &other);
	~ShDimLinearData();

	ShDimLinearData& operator=(const ShDimLinearData &other);

};

class ShDimAlignedData : public ShEntityData {

public:
	ShPoint3d firstOrigin;
	ShPoint3d secondOrigin;
	ShPoint3d firstDim;
	ShPoint3d secondDim;
	ShPoint3d text;

public:
	ShDimAlignedData();
	ShDimAlignedData(const ShPoint3d &firstOrigin, const ShPoint3d &secondOrigin, const ShPoint3d &firstDim, const ShPoint3d &secondDim,
		const ShPoint3d &text);
	ShDimAlignedData(const ShDimAlignedData &other);
	~ShDimAlignedData();

	ShDimAlignedData& operator=(const ShDimAlignedData &other);
};

#endif //_SHENTITYDATA_H