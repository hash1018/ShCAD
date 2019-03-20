
#ifndef _SHEXTENDER_H
#define _SHEXTENDER_H

#include "ShVisitor.h"
#include <qlinkedlist.h>
#include "ShPoint.h"
class ShEntity;
class ShGraphicView;
class ShExtender : public ShVisitor {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> baseEntities;
	ShPoint3d clickPoint;

public:
	ShExtender(ShGraphicView *view, const QLinkedList<ShEntity*>& baseEntities, const ShPoint3d& clickPoint);
	~ShExtender();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);


};

class ShFindIntersectPointLineExtender : public ShVisitor {
	friend class ShExtender;
public:
	enum PointToExtend {
		Start,
		End,
	};

private:
	QLinkedList<ShPoint3d> &intersectPointList;
	ShLine *lineToExtend;
	PointToExtend pointToExtend;

private:
	ShFindIntersectPointLineExtender(ShLine *lineToExtend, QLinkedList<ShPoint3d> &intersectPointList, PointToExtend pointToExtend = Start);
	~ShFindIntersectPointLineExtender();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};

#endif //_SHEXTENDER_H