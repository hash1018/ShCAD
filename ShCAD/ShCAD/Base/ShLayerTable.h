

#ifndef _SHLAYERTABLE_H
#define _SHLAYERTABLE_H

#include <qlist.h>
#include <qlinkedlist.h>

class ShEntity;
class ShLayer;

class ShLayerTable {

private:
	QList<ShLayer*> layerList;
	ShLayer *currentLayer;

public:
	ShLayerTable();
	~ShLayerTable();

	void add(ShLayer *layer);
	void remove(ShLayer *layer);

	void updateTurnOnLayerList();

public:
	void setCurrentLayer(int index) { this->currentLayer = this->layerList.at(index); }
	void setCurrentLayer(ShLayer *layer) { this->currentLayer = layer; }

public:
	inline int getCurrentLayerIndex() const { return this->layerList.indexOf(this->currentLayer); }
	inline ShLayer* getLayer(int index) const { return this->layerList.at(index); }
	inline ShLayer* getCurrentLayer() const { return this->currentLayer; }
	inline int getSize() const { return this->layerList.size(); }
	inline int getIndex(ShLayer *layer) const { return this->layerList.indexOf(layer); }
};

#endif //_SHLAYERTABLE_H