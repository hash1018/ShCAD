


#ifndef _SHLINE_H
#define _SHLINE_H

#include "Entity\ShEntity.h"
#include "ShVector.h"

typedef struct ShLineData {

	ShVector start;
	ShVector end;
	
	ShLineData();
	ShLineData(ShVector& start, ShVector& end);
	ShLineData(const ShLineData& data);
	bool operator==(const ShLineData& data);
	ShLineData& operator=(const ShLineData &data);

}ShLineData;

/* Class for Line entity */

class ShLine : public ShEntity {

protected:
	ShLineData data;

public:
	ShLine();
	ShLine(const ShLineData &data);
	ShLine(const ShLine& other);
	ShLine& operator=(const ShLine& other);
	~ShLine();

	ShLine* Clone();

	ShLineData& GetData() const;
	void SetData(const ShLineData& data);


};

inline ShLineData& ShLine::GetData() const {

	return const_cast<ShLineData&>(this->data);
}

#endif //_SHLINE_H