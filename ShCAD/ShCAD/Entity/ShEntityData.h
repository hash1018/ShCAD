

#ifndef _SHENTITYDATA_H
#define _SHENTITYDATA_H

#include "Data\ShPoint.h"

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


#endif //_SHENTITYDATA_H