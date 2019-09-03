
#ifndef _SHTRIMER_H
#define _SHTRIMER_H

#include "ShVisitor.h"
#include <qlinkedlist.h>
#include "Data\ShPoint.h"

class ShEntity;

class ShTrimer : public ShVisitor {

private:
	QLinkedList<ShEntity*> baseEntities;
	ShPoint3d clickPoint;

private:
	QLinkedList<ShEntity*> &trimedEntities;
	bool &valid;

public:
	ShTrimer(const QLinkedList<ShEntity*> &baseEntities, const ShPoint3d &clickPoint, QLinkedList<ShEntity*> &trimedEntities, bool &valid);
	~ShTrimer();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

private:
	ShPoint3d getClosestByDistance(const ShPoint3d &clickPoint, const QLinkedList<ShPoint3d> &trimPointList);
	ShPoint3d getClosestByAngle(const ShPoint3d &clickPoint, const ShPoint3d &center, const QLinkedList<ShPoint3d> &trimPointList, bool antiClockWise = true);
};


///////////////////////////////////////////////////////////////

class ShLineTrimPointFinder : public ShVisitor {

	friend class ShTrimer;

private:
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList;
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList;
	ShLine *lineToTrim;
	ShPoint3d clickPoint;

private:
	ShLineTrimPointFinder(ShLine *lineToTrim, const ShPoint3d &clickPoint, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList, 
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
	~ShLineTrimPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

private:
	bool checkIntersectLiesOnStartEnd(const ShPoint3d &intersect, const ShPoint3d &start, const ShPoint3d &end);
	void appendTrimPointToList(const ShPoint3d &trimPoint);
	void appendTrimPointToList(const ShPoint3d &trimPoint, const ShPoint3d &trimPoint2);

};

#endif //_SHTRIMER_H