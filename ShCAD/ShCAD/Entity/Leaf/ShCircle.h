

#ifndef _SHCIRCLE_H
#define _SHCIRCLE_H

#include "ShLeaf.h"
#include "ShPoint.h"

typedef struct ShCircleData {

	ShPoint3d center;
	double radius;
	
	ShCircleData();
	ShCircleData(ShPoint3d& center, double radius);
	ShCircleData(const ShCircleData& data);
	bool operator==(const ShCircleData& data);
	ShCircleData& operator=(const ShCircleData &data);

}ShCircleData;

/* Class for Circle entity */

class ShCircle : public ShLeaf {
	
protected:
	ShCircleData data;

public:
	ShCircle();
	ShCircle(const ShCircleData& data);
	ShCircle(const ShCircle& other);
	ShCircle& operator=(const ShCircle& other);
	~ShCircle();

	virtual ShCircle* Clone();
	virtual void Accept(ShVisitor *shVisitor);

	ShCircleData& GetData() const;
	void SetData(const ShCircleData& data);

};

inline ShCircleData& ShCircle::GetData() const {

	return const_cast<ShCircleData&>(this->data);
}

#endif //_SHCIRCLE_H