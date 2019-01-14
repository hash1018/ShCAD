

#ifndef _SHCOMPOSITE_H
#define _SHCOMPOSITE_H

#include "Entity\ShEntity.h"
#include <qlinkedlist.h>

/* This class is the base class that maintains a container of child ShEntity object (children) */
/* Composite pattern */


class ShComposite : public ShEntity {
	
public:
	class Iterator {
		friend class ShComposite;
	private:
		QLinkedList<ShEntity*>::iterator itr;
		QLinkedList<ShEntity*>::iterator begin;
		QLinkedList<ShEntity*>::iterator end;

	public:
		Iterator();
		Iterator(const Iterator& other);
		Iterator& operator=(const Iterator& other);
		~Iterator();

		ShEntity* Current();
		bool IsEnd();
		bool IsBegin();
		void Previous();
		void Next();
	};

protected:
	/* only temporary used */
	QLinkedList<ShEntity*> list;

public:
	ShComposite();
	ShComposite(const ShComposite& other);
	virtual ~ShComposite() = 0;
	ShComposite& operator=(const ShComposite& other);

	virtual ShComposite* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

	virtual bool Add(ShEntity* shEntity);
	virtual void Delete(ShEntity *shEntity);
	virtual void Remove(ShEntity *shEntity);
	
	bool IsListEmpty();
	int GetSize() const;
	ShComposite::Iterator Begin();
	ShComposite::Iterator End();

	
};

inline int ShComposite::GetSize() const {

	return this->list.size();
}



#endif //_SHCOMPOSITE_H
