
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
	void AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& trimPoint,
		QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
	void AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& trimPoint,
		const ShPoint3d& trimPoint2, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
		QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList);
};

#endif //_SHTRIMER_H