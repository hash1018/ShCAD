

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
		QLinkedList<ShEntity*>::iterator first;
		QLinkedList<ShEntity*>::iterator last;

	public:
		Iterator();
		Iterator(const Iterator& other);
		Iterator& operator=(const Iterator& other);
		~Iterator();

		ShEntity* Current();
		bool IsLast();
		bool IsFirst();
		void Previous();
		void Next();
	};

protected:
	/* only temporary used */
	QLinkedList<ShEntity*> list;

	int length;

public:
	ShComposite();
	ShComposite(const ShComposite& other);
	virtual ~ShComposite() = 0;
	ShComposite& operator=(const ShComposite& other);

	virtual ShComposite* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

	virtual bool Add(ShEntity* shEntity) = 0;


	int GetLength() const;
	
	ShComposite::Iterator First();
	ShComposite::Iterator Last();

	
};

inline int ShComposite::GetLength() const {

	return this->length;
}





#endif //_SHCOMPOSITE_H
