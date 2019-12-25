
#ifndef _SHCLOSESTINTERSECTIONPOINTFINDER_H
#define _SHCLOSESTINTERSECTIONPOINTFINDER_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"

class ShEntity;

class ShClosestIntersectionPointFinder : public ShVisitor {

private:
	bool &valid;
	ShPoint3d base;
	ShEntity *another;

	ShPoint3d &intersect;

public:
	ShClosestIntersectionPointFinder(const ShPoint3d &base, ShEntity *another, ShPoint3d &intersect, bool &valid);
	~ShClosestIntersectionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};


///////////////////////////////////////////////////////////////////////

class ShLineClosestIntersectionPointFinder : public ShVisitor {

	friend class ShClosestIntersectionPointFinder;

private:
	bool &valid;
	ShPoint3d base;
	ShLine *another;
	ShPoint3d &intersect;

private:
	ShLineClosestIntersectionPointFinder(const ShPoint3d &base, ShLine *another, ShPoint3d &intersect, bool &valid);
	~ShLineClosestIntersectionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
};


//////////////////////////////////////////////////////////////////////////

class ShCircleClosestIntersectionPointFinder : public ShVisitor {

	friend class ShClosestIntersectionPointFinder;

private:
	bool &valid;
	ShPoint3d base;
	ShCircle *another;
	ShPoint3d &intersect;

private:
	ShCircleClosestIntersectionPointFinder(const ShPoint3d &base, ShCircle *another, ShPoint3d &intersect, bool &valid);
	~ShCircleClosestIntersectionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
};

//////////////////////////////////////////////////////////////////////////

class ShArcClosestIntersectionPointFinder : public ShVisitor {

	friend class ShClosestIntersectionPointFinder;

private:
	bool &valid;
	ShPoint3d base;
	ShArc *another;
	ShPoint3d &intersect;

private:
	ShArcClosestIntersectionPointFinder(const ShPoint3d &base, ShArc *another, ShPoint3d &intersect, bool &valid);
	~ShArcClosestIntersectionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
};

#endif //_SHCLOSESTINTERSECTIONPOINTFINDER_H