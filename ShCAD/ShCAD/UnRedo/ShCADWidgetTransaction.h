
#ifndef _SHCADWIDGETTRANSACTION_H
#define _SHCADWIDGETTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShColor.h"

class ShCADWidget;

class ShChangeColorTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShColor prev;
	ShColor current;

public:
	ShChangeColorTransaction(ShCADWidget *widget, const ShColor &prev, const ShColor &current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeColorTransaction();
};

#endif //_SHCADWIDGETTRANSACTION_H