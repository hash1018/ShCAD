
#ifndef _SHACTIONDATA_H
#define _SHACTIONDATA_H

#include "Data\ShPoint3d.h"

class QMouseEvent;
class QKeyEvent;

class ShActionData {

public:
	ShPoint3d point;
	QMouseEvent *mouseEvent;
	QKeyEvent *keyEvent;

public:
	ShActionData();
	virtual ~ShActionData();
	

};

class ShDecoratorActionData : public ShActionData {

public:
	bool snapAccepted;
	bool orthAccepted;

public:
	ShDecoratorActionData();
	~ShDecoratorActionData();
};


#endif //_SHACTIONDATA_H