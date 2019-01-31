

#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"
#include "ShLayerTable.h"
class ShEntityTable : public ShComposite {

private:
	ShLayerTable layerTable;
	QLinkedList<ShEntity*> justAddedEntityList;


public:
	ShEntityTable();
	ShEntityTable(const ShEntityTable& other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable& other);

	ShEntityTable* Clone();
	void Accept(ShVisitor *shVisitor);
	
	virtual bool Add(ShEntity *shEntity);
	virtual bool Add(QLinkedList<ShEntity*> &list);
	virtual void Remove(ShEntity *shEntity);

	ShEntity* FindEntity(double x, double y, double zoomRate);
	
	inline QLinkedList<ShEntity*>::iterator JustTurnOnLayerBegin() { return this->layerTable.GetJustTurnOnLayer()->Begin(); }
	inline QLinkedList<ShEntity*>::iterator JustTurnOnLayerEnd() { return this->layerTable.GetJustTurnOnLayer()->End(); }
	inline QLinkedList<ShEntity*>::iterator TurnOnLayerBegin() { return this->layerTable.TurnOnListBegin(); }
	inline QLinkedList<ShEntity*>::iterator TurnOnLayerEnd() { return this->layerTable.TurnOnListEnd(); }
	inline QLinkedList<ShEntity*>::iterator JustAddedEntitiesBegin() { return this->justAddedEntityList.begin(); }
	inline QLinkedList<ShEntity*>::iterator JustAddedEntitiesEnd() { return this->justAddedEntityList.end(); }


	inline ShLayerTable* GetLayerTable() { return &(this->layerTable); }
};

#endif //_SHENTITYTABLE_H