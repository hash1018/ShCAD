
#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"
class ShLayerTable;

class ShEntityTable : public ShComposite {

private:
	ShLayerTable *layerTable;
	QLinkedList<ShEntity*> justAddedEntityList;

public:
	ShEntityTable(ShLayerTable *layerTable);
	ShEntityTable(const ShEntityTable &other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable &other);

	ShEntityTable* clone();
	void accept(ShVisitor *visitor);

	virtual bool add(ShEntity *entity);
	virtual bool add(const QLinkedList<ShEntity*> &list);
	virtual bool remove(ShEntity *entity);

	virtual void search(ShSearchEntityStrategy &strategy);

	inline QLinkedList<ShEntity*>::iterator justAddedEntityBegin() { return this->justAddedEntityList.begin(); }
	inline QLinkedList<ShEntity*>::iterator justAddedEntityEnd() { return this->justAddedEntityList.end(); }
	QLinkedList<ShEntity*>::iterator justTurnOnLayerBegin();
	QLinkedList<ShEntity*>::iterator justTurnOnLayerEnd();
	QLinkedList<ShEntity*>::iterator turnOnLayerBegin();
	QLinkedList<ShEntity*>::iterator turnOnLayerEnd();
};

#endif //_SHENTITYTABLE_H