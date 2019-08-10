
#ifndef _SHCADWIDGETTRANSACTION_H
#define _SHCADWIDGETTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShColor.h"
#include "Data\ShLineStyle.h"

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

////////////////////////////////////////////////////////

class ShChangeLineStyleTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShLineStyle prev;
	ShLineStyle current;

public:
	ShChangeLineStyleTransaction(ShCADWidget *widget, const ShLineStyle &prev, const ShLineStyle &current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeLineStyleTransaction();
};

#endif //_SHCADWIDGETTRANSACTION_H