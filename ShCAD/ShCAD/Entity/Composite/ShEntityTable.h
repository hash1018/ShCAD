

#ifndef _SHENTITYTABLE_H
#define _SHENTITYTABLE_H

#include "ShComposite.h"
#include "ShLayerTable.h"
class ShEntityTable : public ShComposite {

private:
	ShLayerTable layerTable;

public:
	ShEntityTable();
	ShEntityTable(const ShEntityTable& other);
	~ShEntityTable();
	ShEntityTable& operator=(const ShEntityTable& other);

	ShEntityTable* Clone();
	void Accept(ShVisitor *shVisitor);
	
	ShEntity* FindEntity(double x, double y, double zoomRate);
	
	inline ShLayerTable* GetLayerTable() { return &(this->layerTable); }
};

#endif //_SHENTITYTABLE_H