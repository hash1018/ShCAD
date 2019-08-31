

#ifndef _SHEXTENDER_H
#define _SHEXTENDER_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"
#include <qlinkedlist.h>

class ShEntity;

enum ShEntityPartToExtend {
	Start,
	End,
};


class ShEntityPartToExtendFinder : public ShVisitor {

	friend class ShExtender;

private:
	ShEntityPartToExtend &entityPartToExtend;
	ShPoint3d &pointToExtend;
	const ShPoint3d clickPoint;

private:
	ShEntityPartToExtendFinder(ShEntityPartToExtend &entityPartToExtend, ShPoint3d &pointToExtend, const ShPoint3d &clickPoint);
	~ShEntityPartToExtendFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShArc *arc);


};

//////////////////////////////////////////////////////


class ShExtender : public ShVisitor {

private:
	QLinkedList<ShEntity*> baseEntities;
	const ShPoint3d clickPoint;

private:
	ShEntity* *extendedEntity;
	bool &valid;

public:
	ShExtender(const QLinkedList<ShEntity*> &baseEntities, const ShPoint3d &clickPoint, ShEntity* *extendedEntity, bool &valid);
	~ShExtender();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};


/////////////////////////////////////////////////////////


class ShExtensionPointFinder : public ShVisitor {

protected:
	QLinkedList<ShPoint3d> &extensionPointList;

protected:
	ShExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList);
	virtual ~ShExtensionPointFinder() = 0;
	
};


//////////////////////////////////////////////////////////



class ShLineExtensionPointFinder : public ShExtensionPointFinder {

	friend class ShExtender;

private:
	const ShLine *const lineToExtend;
	ShEntityPartToExtend entityPartToExtend;

private:
	ShLineExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend);
	~ShLineExtensionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

	bool checkPossibleToExtend(const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint);
	bool checkPossibleToExtend(const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend,
		const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint);
};

///////////////////////////////////////////////////////////


class ShArcExtensionPointFinder : public ShExtensionPointFinder {

	friend class ShExtender;

private:
	const ShArc *const arcToExtend;
	ShEntityPartToExtend entityPartToExtend;

private:
	ShArcExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend);
	~ShArcExtensionPointFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

	bool checkPossibleToExtend(const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint);
	bool checkPossibleToExtend(const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend,
		const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint);

};

#endif //_SHEXETENDER_H