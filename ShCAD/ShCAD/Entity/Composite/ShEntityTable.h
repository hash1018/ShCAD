

#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"

class ShEntityTable : public ShComposite {

public:
	ShEntityTable();
	ShEntityTable(const ShEntityTable& other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable& other);

	ShEntityTable* Clone();
	void Accept(ShVisitor *shVisitor);

	virtual bool Add(ShEntity *shEntity);
	virtual void Delete(ShEntity *shEntity);


};

#endif //_SHENTITYTABLE_H