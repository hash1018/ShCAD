
#ifndef _SHACTIONDATA_H
#define _SHACTIONDATA_H

#include "Data\ShPoint.h"

class QMouseEvent;
class QKeyEvent;

class ShActionData {

public:
	ShPoint3d point;
	ShPoint3d nextPoint;
	QMouseEvent *mouseEvent;
	QKeyEvent *keyEvent;

public:
	ShActionData();
	~ShActionData();
	

};


#endif //_SHACTIONDATA_H