
#ifndef _SHENTITYTRANSACTION_H
#define _SHENTITYTRANSCATION_H

#include "ShTransaction.h"
#include <qlinkedlist.h>
#include "Data\ShPoint.h"

class ShCADWidget;
class ShEntity;
class ShAddEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> list;
	bool mustDeleteEntity;

public:
	ShAddEntityTransaction(ShCADWidget *widget, const QString &transactionName);
	~ShAddEntityTransaction();

	virtual void redo();
	virtual void undo();

	void add(ShEntity *entity);
	void add(const QLinkedList<ShEntity*> &list);

};

class ShMoveEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> list;
	double disX;
	double disY;

public:
	ShMoveEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, double disX, double disY);
	~ShMoveEntityTransaction();

	virtual void redo();
	virtual void undo();

};

class ShRotateEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> list;
	ShPoint3d center;
	double angle;

public:
	ShRotateEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, const ShPoint3d &center, double angle);
	~ShRotateEntityTransaction();

	virtual void redo();
	virtual void undo();

};

#endif //_SHENTITYTRANSACTION_H