
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

public:
	ShSearchEntityStrategy(double x, double y, double zoomRate);
	virtual ~ShSearchEntityStrategy() = 0;

	void setList(const QLinkedList<ShEntity*> &list);
	virtual void search() = 0;

};

///////////////////////////////////////

class ShSearchEntityUniqueStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate);
	~ShSearchEntityUniqueStrategy();

	virtual void search();

};

class ShSearchEntityCompositeChildIncludedStrategy : public ShSearchEntityStrategy {

protected:
	ShEntity* *foundEntity;

public:
	ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate);
	~ShSearchEntityCompositeChildIncludedStrategy();

	virtual void search();

};


#endif //_SHSEARCHENTITYSTRATEGY_H