


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

class ShLineMemento;
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

	ShLineData& GetData() const;
	void SetData(const ShLineData& data);


	ShLineMemento* CreateMemento();
	void SetMemento(const ShLineMemento* memento);

};

inline ShLineData& ShLine::GetData() const {

	return const_cast<ShLineData&>(this->data);
}

#endif //_SHLINE_H