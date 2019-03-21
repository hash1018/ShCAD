
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

class ShFindExtensionPointer : public ShVisitor {

protected:
	QLinkedList < ShPoint3d> &extensionPointList;

protected:
	ShFindExtensionPointer(QLinkedList<ShPoint3d> &extensionPointList) 
		:extensionPointList(extensionPointList) {}

	virtual ~ShFindExtensionPointer() = 0 {}


};

class ShFindExtensionPointLineExtender : public ShFindExtensionPointer {
	friend class ShExtender;
public:
	enum PointToExtend {
		Start,
		End,
	};

private:
	ShLine *lineToExtend;
	PointToExtend pointToExtend;

private:
	ShFindExtensionPointLineExtender(ShLine *lineToExtend, QLinkedList<ShPoint3d> &extensionPointList, PointToExtend pointToExtend = Start);
	~ShFindExtensionPointLineExtender();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

	bool CheckPossibleToExtend(ShLine *lineToExtend, PointToExtend pointToExtend, const ShPoint3d& extensionPoint);
	bool CheckPossibleToExtend(ShLine *lineToExtend, PointToExtend pointToExtend, const ShPoint3d& extensionPoint,
		const ShPoint3d& extensionPoint2, ShPoint3d& finalExtensionPoint);
};

class ShFindExtensionPointArcExtender : public ShFindExtensionPointer {
	friend class ShExtender;

public:
	enum PointToExtend {
		Start,
		End,
	};
	
private:
	ShArc *arcToExtend;
	PointToExtend pointToExtend;

private:
	ShFindExtensionPointArcExtender(ShArc *arcToExtend, QLinkedList<ShPoint3d> &extensionPointList, PointToExtend pointToExtend = Start);
	~ShFindExtensionPointArcExtender();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};
#endif //_SHEXTENDER_H