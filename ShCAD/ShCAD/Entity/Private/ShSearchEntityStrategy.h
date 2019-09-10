
#ifndef _SHSEARCHENTITYSTRATEGY_H
#define _SHSEARCHENTITYSTRATEGY_H

#include <qlinkedlist.h>

class ShEntity;

class ShSearchEntityStrategy {

protected:
	QLinkedList<ShEntity*> list;
	double x;
	double y;
	double zoomRate;
	double tolerance;
public:
	ShSearchEntityStrategy(double x, double y, double zoomRate, double tolerance = 6.0);
	virtual ~ShSearchEntityStrategy() = 0;

	void setList(const QLinkedList<ShEntity*> &list);
	virtual void search() = 0;

};

///////////////////////////////////////

class ShSearchEntityUniqueStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate, double tolerance = 6.0);
	~ShSearchEntityUniqueStrategy();

	virtual void search();

};

class ShSearchEntityCompositeChildIncludedStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate, double tolerance = 6.0);
	~ShSearchEntityCompositeChildIncludedStrategy();

	virtual void search();

};

class ShSearchEntityDuplicateStrategy : public ShSearchEntityStrategy {

protected:
	QLinkedList<ShEntity*> &foundEntities;
	int max;

public:
	ShSearchEntityDuplicateStrategy(QLinkedList<ShEntity*> &foundEntities, int max, double x, double y, double zoomRate, double tolerance = 6.0);
	~ShSearchEntityDuplicateStrategy();

	virtual void search();

};

#endif //_SHSEARCHENTITYSTRATEGY_H