

#ifndef _SHLAYERTABLE_H
#define _SHLAYERTABLE_H

#include <qlist.h>
#include "ShLayer.h"
#include <qlinkedlist.h>
class ShEntity;
class ShLayerTable {
	friend class ShEntityTable;
private:
	QList<ShLayer*> list;
	ShLayer *currentLayer;
	QLinkedList<ShEntity*> turnOnList;
	ShLayer *justTurnOnLayer;

public:
	ShLayerTable();
	~ShLayerTable();
	
	void Add(ShLayer *layer);
	//void Delete(ShLayer *layer);
	void Remove(ShLayer *layer);

	void SetCurrentLayerIndex(int index);
	void SetCurrentLayer(ShLayer* layer);

	void UpdateTurnOnLayerList();

	inline  ShLayer* GetLayer(int index)  { return this->list.at(index); }
	inline  ShLayer* GetCurrentLayer()  { return this->currentLayer; }
	int GetCurrentLayerIndex();
	inline int GetSize() const { return this->list.size(); }

	void SetJustTurnOnLayer(ShLayer *layer) { this->justTurnOnLayer = layer; }
	inline ShLayer* GetJustTurnOnLayer() { return this->justTurnOnLayer; }
	
	inline QLinkedList<ShEntity*>::iterator TurnOnListBegin() { return this->turnOnList.begin(); }
	inline QLinkedList<ShEntity*>::iterator TurnOnListEnd() { return this->turnOnList.end(); }

};

#endif //_SHLAYERTABLE_H