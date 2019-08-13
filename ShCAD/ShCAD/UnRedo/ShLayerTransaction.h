
#ifndef _SHLAYERTRANSACTION_H
#define _SHLAYERTRANSACTION_H

#include "ShTransaction.h"

class ShCADWidget;
class ShLayer;

class ShChangeCurrentLayerTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShLayer *prev;
	ShLayer *current;

public:
	ShChangeCurrentLayerTransaction(ShCADWidget *widget, ShLayer *prev, ShLayer *current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeCurrentLayerTransaction();

};

#endif //_SHLAYERTRANSACTION_H