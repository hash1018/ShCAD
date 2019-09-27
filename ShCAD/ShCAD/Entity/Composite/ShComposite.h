
#ifndef _SHCOMPOSITE_H
#define _SHCOMPOSITE_H

#include "Entity\ShEntity.h"
#include <qlinkedlist.h>
class ShSearchEntityStrategy;

class ShComposite : public ShEntity {

protected:
	QLinkedList<ShEntity*> list;

public:
	ShComposite();
	ShComposite(const ShPropertyData &propertyData, ShLayer *layer);
	ShComposite(const ShComposite &other);
	virtual ~ShComposite() = 0;
	ShComposite& operator=(const ShComposite &other);

	virtual bool add(ShEntity *entity);
	virtual bool add(const QLinkedList<ShEntity*> &list);

	virtual bool deleteEntity(ShEntity *entity);
	virtual bool remove(ShEntity *entity);

	virtual void search(ShSearchEntityStrategy &strategy);

	inline bool isEmpty() const { return this->list.isEmpty(); }
	inline int getSize() const { return this->list.size(); }
	inline QLinkedList<ShEntity*>::iterator begin() { return this->list.begin(); }
	inline QLinkedList<ShEntity*>::iterator end() { return this->list.end(); }
};

#endif //_SHCOMPOSITE_H