
#ifndef _SHENTITYTRANSACTION_H
#define _SHENTITYTRANSCATION_H

#include "ShTransaction.h"
#include <qlinkedlist.h>

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

#endif //_SHENTITYTRANSACTION_H