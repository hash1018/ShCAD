
#ifndef _SHSTRETCHVISITOR_H
#define _SHSTRETCHVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"

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
};


class ShStretchData {

public:
	ShStretchData();
	virtual ~ShStretchData() = 0;

};

class ShStretchLeafData : public ShStretchData {

	friend class ShStretchVisitor;
	friend class ShPossibleEntityToStretchFinder;

private:
	StretchPoint stretchPoint;

protected:
	ShStretchLeafData(StretchPoint stretchPoint);
	~ShStretchLeafData();

};


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

public:
	void setOriginal(ShEntity *original) { this->original = original; }
	void setStretchData(ShStretchData *stretchData) { this->stretchData = stretchData; }
};


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

};

#endif //_SHSTRETCHVISITOR_H