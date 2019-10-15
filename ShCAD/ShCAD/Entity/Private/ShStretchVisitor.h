
#ifndef _SHSTRETCHVISITOR_H
#define _SHSTRETCHVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"

class ShEntity;

enum StretchPoint {

	StretchNothing,
	StretchMove,
	StretchStart,
	StretchEnd,
	StretchMid,
	StretchLeft,
	StretchBottom,
	StretchRight,
	StretchTop,
	StretchChild,
	StretchFirstOrigin,
	StretchSecondOrigin,
	StretchFirstDim,
	StretchSecondDim,
	StretchCenter,
	StretchBoundary,
	StretchBoundary2,
	StretchText,
};

////////////////////////////////////////////////////

class ShStretchData {

public:
	ShStretchData();
	virtual ~ShStretchData() = 0;

};

////////////////////////////////////////////////////

class ShStretchLeafData : public ShStretchData {

	friend class ShStretchVisitor;
	friend class ShPossibleEntityToStretchFinder;
	friend class ShStretchDataForMoveCreator;
	friend class ShStretchPointRectFinder;

private:
	StretchPoint stretchPoint;

protected:
	ShStretchLeafData(StretchPoint stretchPoint);
	~ShStretchLeafData();

};


//////////////////////////////////////////////////////

class ShStretchVisitor : public ShVisitor {

private:
	ShPoint3d base;
	ShPoint3d current;
	ShEntity *original;
	ShStretchData *stretchData;

public:
	ShStretchVisitor(const ShPoint3d &base, const ShPoint3d &current);
	~ShStretchVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);

public:
	void setOriginal(ShEntity *original) { this->original = original; }
	void setStretchData(ShStretchData *stretchData) { this->stretchData = stretchData; }
};

////////////////////////////////////////////////////////


class ShPossibleEntityToStretchFinder : public ShVisitor {

private:
	ShPoint3d point;
	bool &possible;
	ShStretchData* *stretchData;

public:
	ShPossibleEntityToStretchFinder(const ShPoint3d &point, bool &possible, ShStretchData* *stretchData);
	~ShPossibleEntityToStretchFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
};

/////////////////////////////////////////////////////////

class ShStretchDataForMoveCreator : public ShVisitor {

private:
	ShStretchData* *stretchData;

public:
	ShStretchDataForMoveCreator(ShStretchData* *stretchData);
	~ShStretchDataForMoveCreator();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);

};

//////////////////////////////////////////////////////////

class ShStretchPointRectFinder : public ShVisitor {

private:
	ShPoint3d topLeft;
	ShPoint3d bottomRight;
	ShStretchData* *stretchData;

public:
	ShStretchPointRectFinder(const ShPoint3d &topLeft, const ShPoint3d &bottomRight, ShStretchData* *stretchData);
	~ShStretchPointRectFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);

private:
	bool checkPointLiesInsideRect(const ShPoint3d &point);
};

#endif //_SHSTRETCHVISITOR_H