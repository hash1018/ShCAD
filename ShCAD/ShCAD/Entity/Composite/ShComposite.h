

#ifndef _SHCOMPOSITE_H
#define _SHCOMPOSITE_H

#include "Entity\ShEntity.h"
#include <qlinkedlist.h>

/* This class is the base class that maintains a container of child ShEntity object (children) */
/* Composite pattern */


class ShComposite : public ShEntity {


protected:
	/* only temporary used */
	QLinkedList<ShEntity*> list;

	

public:
	ShComposite();
	ShComposite(const ShPropertyData &propertyData, ShLayer *layer);
	ShComposite(const ShComposite& other);
	virtual ~ShComposite() = 0;
	ShComposite& operator=(const ShComposite& other);

	virtual ShComposite* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

	virtual bool Add(ShEntity* shEntity);
	virtual bool Add(QLinkedList<ShEntity*> &list);

	virtual void Delete(ShEntity *shEntity);
	virtual void Remove(ShEntity *shEntity);
	
	bool IsListEmpty();
	int GetSize() const;
	inline QLinkedList<ShEntity*>::iterator Begin() { return this->list.begin(); }
	inline QLinkedList<ShEntity*>::iterator End() { return this->list.end(); }

	ShEntity* GetEntity(int index);
	int GetIndex(ShEntity* entity);

protected:
	void RemoveAll(QLinkedList<ShEntity*> &list);
};

inline int ShComposite::GetSize() const {

	return this->list.size();
}



#endif //_SHCOMPOSITE_H
