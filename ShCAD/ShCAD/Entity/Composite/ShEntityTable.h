

#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"

class ShEntityTable : public ShComposite {

private:
	QLinkedList<ShEntity*> justAddedEntityList;

public:
	ShEntityTable();
	ShEntityTable(const ShEntityTable& other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable& other);

	ShEntityTable* Clone();
	void Accept(ShVisitor *shVisitor);
	
	ShEntity* FindEntity(double x, double y, double zoomRate);
	

};

#endif //_SHENTITYTABLE_H