
#ifndef _SHTRIMER_H
#define _SHTRIMER_H

#include "ShVisitor.h"
#include <qlinkedlist.h>
#include "ShPoint.h"
class ShEntity;
class ShGraphicView;
class ShTrimer : public ShVisitor {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> baseEntities;
	ShPoint3d clickPoint;

public:
	ShTrimer(ShGraphicView *view, const QLinkedList<ShEntity*>& baseEntities, const ShPoint3d& clickPoint);
	~ShTrimer();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

private:
	ShPoint3d GetClosestPointByDistance(const ShPoint3d& clickPoint, const QLinkedList<ShPoint3d>& trimPointList);
	ShPoint3d GetClosestPointByAngle(const ShPoint3d& clickPoint, const ShPoint3d& center,
		const QLinkedList<ShPoint3d>& trimPointList, bool antiClockWise = true);
	void CreateCommand(ShEntity *original, ShEntity *trimedEntity, ShEntity *trimedEntity2 = 0);
};

class ShFindTrimPointLineTrimer : public ShVisitor {
	friend class ShTrimer;
private:
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList;
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList;
	ShLine *lineToTrim;
	ShPoint3d clickPoint;
	
private:
	ShFindTrimPointLineTrimer(ShLine *lineToTrim, const ShPoint3d& clickPoint,
		QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
	~ShFindTrimPointLineTrimer();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

private:
	void OneIntersectLiesOnBaseEntity(ShLine *lineToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect,
		QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);

	void TwoIntersectsLieOnBaseEntity(ShLine *lineToTrim, const ShPoint3d& clickPoint, 
		const ShPoint3d& intersect, const ShPoint3d& intersect2,
		QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);


	void AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& trimPoint,
		QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
	void AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& trimPoint,
		const ShPoint3d& trimPoint2, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
};

class ShFindTrimPointCircleTrimer : public ShVisitor {
	friend class ShTrimer;

private:
	QLinkedList<ShPoint3d> &clockWiseTrimPointList;
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList;
	ShCircle *circleToTrim;
	ShPoint3d clickPoint;

private:
	ShFindTrimPointCircleTrimer(ShCircle *circleToTrim, const ShPoint3d& clickPoint,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);
	~ShFindTrimPointCircleTrimer();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

private:
	void TwoIntersectsLieOnBaseEntity(ShCircle *circleToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect, const ShPoint3d& intersect2,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);

};

class ShFindTrimPointArcTrimer : public ShVisitor {
	friend class ShTrimer;

private:
	QLinkedList<ShPoint3d> &clockWiseTrimPointList;
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList;
		ShArc *arcToTrim;
		ShPoint3d clickPoint;

private:
	ShFindTrimPointArcTrimer(ShArc *arcToTrim,const ShPoint3d& clickPoint,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);
	~ShFindTrimPointArcTrimer();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

private:
	void OneIntersectLiesOnBaseEntity(ShArc *arcToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);
	void TwoIntersectsLieOnBaseEntity(ShArc *arcToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect, const ShPoint3d& intersect2,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);

	void OneIntersectLiesOnArcToTrim(ShArc *arcToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);

	void TwoIntersectsLieOnArcToTrim(ShArc *arcToTrim, const ShPoint3d& clickPoint,
		const ShPoint3d& intersect, const ShPoint3d& intersect2,
		QLinkedList<ShPoint3d> &clockWiseTrimPointList,
		QLinkedList<ShPoint3d> &antiClockWiseTrimPointList);


};
#endif //_SHTRIMER_H