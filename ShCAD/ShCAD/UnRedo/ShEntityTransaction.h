
#ifndef _SHENTITYTRANSACTION_H
#define _SHENTITYTRANSCATION_H

#include "ShTransaction.h"
#include <qlinkedlist.h>
#include "Data\ShPoint3d.h"

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

class ShMirrorEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> list;
	ShPoint3d center;
	double angle;

public:
	ShMirrorEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, const ShPoint3d &center, double angle);
	~ShMirrorEntityTransaction();

	virtual void redo();
	virtual void undo();

};

class ShRemoveEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> list;
	bool mustDeleteEntity;

public:
	ShRemoveEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list);
	~ShRemoveEntityTransaction();

	virtual void redo();
	virtual void undo();

};


class ShExtendEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> originalList;
	QLinkedList<ShEntity*> extendedList;
	bool mustDeleteOriginal;
	bool mustDeleteExtended;

public:
	ShExtendEntityTransaction(ShCADWidget *widget);
	~ShExtendEntityTransaction();

	virtual void redo();
	virtual void undo();

public:
	void addOriginalList(ShEntity *entity) { this->originalList.append(entity); }
	void addExtendedList(ShEntity *entity) { this->extendedList.append(entity); }
	void removeExtendedList(ShEntity *entity) { this->extendedList.removeOne(entity); }


public:
	inline bool containsInExtendedList(ShEntity *entity) const { return this->extendedList.contains(entity); }
};


class ShTrimEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> originalList;
	QLinkedList<ShEntity*> trimedList;
	bool mustDeleteOriginal;
	bool mustDeleteTrimed;

public:
	ShTrimEntityTransaction(ShCADWidget *widget);
	~ShTrimEntityTransaction();

	virtual void redo();
	virtual void undo();

public:
	void addOriginalList(ShEntity *entity) { this->originalList.append(entity); }
	void addTrimedList(ShEntity *entity) { this->trimedList.append(entity); }
	void removeTrimedList(ShEntity *entity) { this->trimedList.removeOne(entity); }


public:
	inline bool containsInTrimedList(ShEntity *entity) const { return this->trimedList.contains(entity); }

};

class ShStretchEntityTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> originalEntities;
	QLinkedList<ShEntity*> stretchedEntities;
	bool mustDeleteOriginal;
	bool mustDeleteStretched;

public:
	ShStretchEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &originalEntities, const QLinkedList<ShEntity*> &stretchedEntities);
	~ShStretchEntityTransaction();

	virtual void redo();
	virtual void undo();

};

#endif //_SHENTITYTRANSACTION_H