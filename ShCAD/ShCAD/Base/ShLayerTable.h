

#ifndef _SHLAYERTABLE_H
#define _SHLAYERTABLE_H

#include <qlist.h>
#include <qlinkedlist.h>

class ShEntity;
class ShLayer;

class ShLayerTable {
	friend class ShEntityTable;
private:
	QList<ShLayer*> layerList;
	ShLayer *currentLayer;
	ShLayer *justTurnOnLayer;
	QLinkedList<ShEntity*> turnOnList;
	


public:
	ShLayerTable();
	~ShLayerTable();

	void add(ShLayer *layer);
	void remove(ShLayer *layer);

	void updateTurnOnLayerList();

public:
	void setCurrentLayer(int index) { this->currentLayer = this->layerList.at(index); }
	void setCurrentLayer(ShLayer *layer) { this->currentLayer = layer; }
	void setJustTurnOnLayer(ShLayer *layer) { this->justTurnOnLayer = layer; }

public:
	inline int getCurrentLayerIndex() const { return this->layerList.indexOf(this->currentLayer); }
	inline ShLayer* getLayer(int index) const { return this->layerList.at(index); }
	inline ShLayer* getCurrentLayer() const { return this->currentLayer; }
	inline int getSize() const { return this->layerList.size(); }
	inline int getIndex(ShLayer *layer) const { return this->layerList.indexOf(layer); }
	inline ShLayer* getJustTurnOnLayer() const { return this->justTurnOnLayer; }
	inline QLinkedList<ShEntity*>::iterator turnOnListBegin() { return this->turnOnList.begin(); }
	inline QLinkedList<ShEntity*>::iterator turnOnListEnd() { return this->turnOnList.end(); }
};

#endif //_SHLAYERTABLE_H