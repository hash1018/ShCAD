
#ifndef _SHCHANGECURRENTACTIONSTRATEGY_H
#define _SHCHANGECURRENTACTIONSTRATEGY_H

#include "ShVariable.h"

class ShGraphicView;
class ShChangeCurrentActionStrategy {
	friend class ShGraphicView;
protected:
	ShGraphicView *view;
	ActionType newActionType;

public:
	ShChangeCurrentActionStrategy(ActionType newActionType);
	virtual ~ShChangeCurrentActionStrategy() = 0;
	void SetView(ShGraphicView *view) { this->view = view; }

protected:
	virtual ActionType Change();

private:
	//*** Not allowed to be created in heap area. stack only.
	void *operator new(size_t) {}
	//*** Not allowed to be created in heap area. stack only.
	void *operator new[](size_t) {}

};

class ShChangeCurrentActionCancelCurrent : public ShChangeCurrentActionStrategy {

public:
	ShChangeCurrentActionCancelCurrent(ActionType newActionType);
	~ShChangeCurrentActionCancelCurrent();

private:
	virtual ActionType Change();

};

class ShChangeCurrentActionCurrentFinished : public ShChangeCurrentActionStrategy {

public:
	ShChangeCurrentActionCurrentFinished(ActionType newActionType);
	~ShChangeCurrentActionCurrentFinished();

private:
	virtual ActionType Change();

};


#endif //_SHCHANGECURRENTACTIONSTRATEGY_H