
#ifndef _SHLAYERTRANSACTION_H
#define _SHLAYERTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShPropertyData.h"

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

/////////////////////////////////////////////

class ShChangeLayerDataTransaction : public ShTransaction {

public:
	enum ChangedType {
		Color,
	};

private:
	ShCADWidget *widget;
	ShLayer *layer;
	ShPropertyData prev;
	ShPropertyData current;
	ChangedType changedType;

public:
	ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const ShPropertyData &prev, const ShPropertyData &current, ChangedType changedType);
	
	virtual void redo();
	virtual void undo();

protected:
	~ShChangeLayerDataTransaction();

};

#endif //_SHLAYERTRANSACTION_H