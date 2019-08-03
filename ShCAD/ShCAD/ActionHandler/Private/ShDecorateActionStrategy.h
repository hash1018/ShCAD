
#ifndef _SHDECORATEACTIONSTRATEGY_H
#define _SHDECORATEACTIONSTRATEGY_H

#include "ShChangeActionStrategy.h"

class ShDecorateActionStrategy : public ShChangeActionStrategy {

public:
	ShDecorateActionStrategy();
	virtual ~ShDecorateActionStrategy() = 0;

};

////////////////////////////////////////////////

class ShDecorateOrthogonalActionStrategy : public ShDecorateActionStrategy {

public:
	ShDecorateOrthogonalActionStrategy();
	~ShDecorateOrthogonalActionStrategy();

protected:
	virtual void change();

};

////////////////////////////////////////////////

class ShDecorateDisposableSnapActionStrategy : public ShDecorateActionStrategy {

private:
	ObjectSnap objectSnap;

public:
	ShDecorateDisposableSnapActionStrategy(ObjectSnap objectSnap);
	~ShDecorateDisposableSnapActionStrategy();

protected:
	virtual void change();

};

#endif //_SHDECORATEACTIONSTRATEGY_H