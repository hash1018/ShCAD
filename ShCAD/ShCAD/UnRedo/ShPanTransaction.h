

#ifndef _SHPANTRANSACTION_H
#define _SHPANTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShPoint3d.h"

class ShCADWidget;

class ShPanTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShPoint3d coordinate;
	int dx;
	int dy;

public:
	ShPanTransaction(ShCADWidget *widget, const ShPoint3d &coordinate, int dx, int dy);
	
	virtual void undo();
	virtual void redo();

protected:
	~ShPanTransaction();

};


#endif //_SHPANTRANSACTION_H


