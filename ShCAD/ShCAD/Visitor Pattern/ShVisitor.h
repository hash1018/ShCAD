

#ifndef _SHVISITOR_H
#define _SHVISITOR_H


class ShLine;
class ShEntityTable;
class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void Visit(ShLine* shLine) = 0;
	void Visit(ShEntityTable *shEntityTable) {}

};


#endif //_SHVISITOR_H