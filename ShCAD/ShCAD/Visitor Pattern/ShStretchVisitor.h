

#ifndef _SHSELECTIONMOVER_H
#define _SHSELECTIONMOVER_H

#include "ShVisitor.h"
#include "ShVariable.h"
#include "ShPoint.h"
class ShEntity;
class ShStretchVisitor : public ShVisitor {

private:
	ShPoint3d base;
	ShPoint3d current;
	VertexPoint vertexPoint;
	ShEntity *original;
public:
	ShStretchVisitor(const ShPoint3d& base, const ShPoint3d& current);
	~ShStretchVisitor();
	
	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

	void SetVertexPoint(VertexPoint point) { this->vertexPoint = point; }
	void SetOriginalEntity(ShEntity *entity) { this->original = entity; }

};


class ShFindStretchMovePointVisitor : public ShVisitor {

private:
	VertexPoint &vertexPoint;
	
public:
	ShFindStretchMovePointVisitor(VertexPoint &vertexPoint);
	~ShFindStretchMovePointVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};

class ShFindStretchPointWithRectVisitor : public ShVisitor {

private:
	VertexPoint &vertexPoint;
	ShPoint3d topLeft;
	ShPoint3d bottomRight;

public:
	ShFindStretchPointWithRectVisitor(VertexPoint &vertexPoint, const ShPoint3d& topLeft, const ShPoint3d& bottomRight);
	~ShFindStretchPointWithRectVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};

#endif //_SHSELECTIONMOVER_H