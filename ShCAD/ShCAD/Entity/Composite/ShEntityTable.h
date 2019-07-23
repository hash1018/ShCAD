
#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"

class ShEntityTable : public ShComposite {

private:
	QLinkedList<ShEntity*> justAddedEntityList;

public:
	ShEntityTable();
	ShEntityTable(const ShEntityTable &other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable &other);

	ShEntityTable* clone();
	void accept(ShVisitor *visitor);

	virtual bool add(ShEntity *entity);
	virtual bool add(const QLinkedList<ShEntity*> &list);
	virtual bool remove(ShEntity *entity);

	inline QLinkedList<ShEntity*>::iterator justAddedEntityBegin() { return this->justAddedEntityList.begin(); }
	inline QLinkedList<ShEntity*>::iterator justAddedEntityEnd() { return this->justAddedEntityList.end(); }
};

#endif //_SHENTITYTABLE_H