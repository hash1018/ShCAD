
#ifndef _SHENTITYTRANSACTION_H
#define _SHENTITYTRANSCATION_H

#include "ShTransaction.h"
#include <qlinkedlist.h>
#include "Data\ShPoint3d.h"
#include "Data\ShPropertyData.h"

class ShCADWidget;
class ShEntity;
class ShLayer;
class ShDimensionStyle;
class ShDim;

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

class ShChangeEntityPropertyDataTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> entities;
	QLinkedList<ShPropertyData> prev;
	QLinkedList<ShPropertyData> current;

public:
	ShChangeEntityPropertyDataTransaction(ShCADWidget *widget);
	~ShChangeEntityPropertyDataTransaction();

	virtual void redo();
	virtual void undo();

	void add(ShEntity *entity, const ShPropertyData &prev, const ShPropertyData &current);
};

class ShChangeEntityLayerTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShEntity*> entities;
	QLinkedList<ShLayer*> prev;
	QLinkedList<ShLayer*> current;

public:
	ShChangeEntityLayerTransaction(ShCADWidget *widget);
	~ShChangeEntityLayerTransaction();

	virtual void redo();
	virtual void undo();

	void add(ShEntity *entity, ShLayer *prev, ShLayer *current);

};

class ShChangeDimDimensionStyleTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	QLinkedList<ShDim*> dims;
	QLinkedList<ShDimensionStyle*> prev;
	QLinkedList<ShDimensionStyle*> current;

public:
	ShChangeDimDimensionStyleTransaction(ShCADWidget *widget);
	~ShChangeDimDimensionStyleTransaction();

	virtual void redo();
	virtual void undo();

	void add(ShDim *dim, ShDimensionStyle *prev, ShDimensionStyle *current);
};

#endif //_SHENTITYTRANSACTION_H