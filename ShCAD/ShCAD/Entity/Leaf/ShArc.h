

#ifndef _SHARC_H
#define _SHARC_H

#include "ShLeaf.h"
#include "ShVector.h"

typedef struct ShArcData {

	ShVector center;
	double radius;
	double startAngle;
	double endAngle;


	ShArcData();
	ShArcData(ShVector& center, double radius, double startAngle, double endAngle);
	ShArcData(const ShArcData& data);
	bool operator==(const ShArcData& data);
	ShArcData& operator=(const ShArcData &data);

}ShArcData;

/* Class for Arc entity */

class ShArc : public ShLeaf {

protected:
	ShArcData data;

public:
	ShArc();
	ShArc(const ShArcData& data);
	ShArc(const ShArc& other);
	ShArc& operator=(const ShArc& other);
	~ShArc();

	ShArc* Clone();
	virtual void Accept(ShVisitor *shVisitor);

	ShArcData& GetData() const;
	void SetData(const ShArcData& data);


};

inline ShArcData& ShArc::GetData() const {

	return const_cast<ShArcData&>(this->data);
}

#endif //_SHARC_H