
#ifndef _SHDIMENSIONSTYLETRANSACTION_H
#define _SHDIMENSIONSTYLETRANSACTION_H

#include "ShTransaction.h"

class ShCADWidget;
class ShDimensionStyle;

class ShChangeCurrentDimensionStyleTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShDimensionStyle *prev;
	ShDimensionStyle *current;

public:
	ShChangeCurrentDimensionStyleTransaction(ShCADWidget *widget, ShDimensionStyle *prev, ShDimensionStyle *current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeCurrentDimensionStyleTransaction();

};

#endif //_SHDIMENSIONSTYLETRANSACTION_H