

#ifndef _SHLAYERTABLE_H
#define _SHLAYERTABLE_H

#include <qlist.h>

class ShLayer;
class ShLayerTable {

private:
	QList<ShLayer*> list;
	ShLayer *currentLayer;

public:
	ShLayerTable();
	~ShLayerTable();
	
	void Add(ShLayer *layer);
	void Delete(ShLayer *layer);

	void SetCurrentLayerIndex(int index);
	void SetCurrentLayer(ShLayer* layer);

	inline  ShLayer* GetLayer(int index)  { return this->list.at(index); }
	inline  ShLayer* GetCurrentLayer()  { return this->currentLayer; }
	int GetCurrentLayerIndex();
	inline int GetSize() const { return this->list.size(); }

	
};

#endif //_SHLAYERTABLE_H