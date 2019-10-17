
#ifndef _SHCADWIDGETTRANSACTION_H
#define _SHCADWIDGETTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShColor.h"
#include "Data\ShLineStyle.h"
#include "Data\ShPoint3d.h"

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

////////////////////////////////////////////////////////////

class ShChangeAxisPositionTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShPoint3d prevCenter;
	ShPoint3d currentCenter;

public:
	ShChangeAxisPositionTransaction(ShCADWidget *widget, const ShPoint3d &prevCenter, const ShPoint3d &currentCenter);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeAxisPositionTransaction();
};

#endif //_SHCADWIDGETTRANSACTION_H