
#ifndef _SHSELECTEDENTITIES_H
#define _SHSELECTEDENTITIES_H

#include "ShComposite.h"

class ShSelectedEntities : public ShComposite {

private:
	QLinkedList<ShEntity*> justSelectedList;

public:
	ShSelectedEntities();
	~ShSelectedEntities();

	virtual bool add(ShEntity *entity);
	virtual bool add(const QLinkedList<ShEntity*> &list);

	virtual bool deleteEntity(ShEntity *entity);
	virtual bool remove(ShEntity *entity);
	virtual bool remove(const QLinkedList<ShEntity*> &list);
	
	void unSelectAll();

	virtual ShSelectedEntities* clone();
	virtual void accept(ShVisitor *visitor);

public:
	inline QLinkedList<ShEntity*>::iterator getJustSelectedBegin() { return this->justSelectedList.begin(); }
	inline QLinkedList<ShEntity*>::iterator getJustSelectedEnd() { return this->justSelectedList.end(); }
};

#endif //_SHSELECTEDENTITIES_H