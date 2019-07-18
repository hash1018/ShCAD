
#ifndef _SHCHANGEACTIONSTRATEGY_H
#define _SHCHANGEACTIONSTRATEGY_H

#include "Base\ShVariable.h"

class ShCADWidget;
class ShActionHandler;
class ShTemporaryAction;

class ShChangeActionStrategy {
	friend class ShCADWidget;

protected:
	ShCADWidget *widget;
	

public:
	ShChangeActionStrategy();
	virtual ~ShChangeActionStrategy() = 0;

protected:
	virtual void change() = 0;

};

//////////////////////////////////////////////////////

class ShChangeActionAfterCancelingCurrentStrategy : public ShChangeActionStrategy {

private:
	ActionType typeToChange;

public:
	ShChangeActionAfterCancelingCurrentStrategy(ActionType typeToChange);
	~ShChangeActionAfterCancelingCurrentStrategy();

protected:
	virtual void change();
};

///////////////////////////////////////////////////////

class ShChangeDefaultAfterFinishingCurrentStrategy : public ShChangeActionStrategy {

public:
	ShChangeDefaultAfterFinishingCurrentStrategy();
	~ShChangeDefaultAfterFinishingCurrentStrategy();

protected:
	virtual void change();

};

///////////////////////////////////////////////////////

class ShChangeTemporaryStrategy : public ShChangeActionStrategy {

private:
	ShTemporaryAction *temporaryAction;
	ShActionHandler *previousAction;

public:
	ShChangeTemporaryStrategy(ShTemporaryAction *temporaryAction, ShActionHandler *previousAction);
	~ShChangeTemporaryStrategy();

protected:
	virtual void change();

};


///////////////////////////////////////////////////////

class ShReturnToPreviousFromTemporaryStrategy : public ShChangeActionStrategy {

private:
	ShTemporaryAction *temporaryAction;

public:
	ShReturnToPreviousFromTemporaryStrategy(ShTemporaryAction *temporaryAction);
	~ShReturnToPreviousFromTemporaryStrategy();

protected:
	virtual void change();

};

#endif //_SHCHANGEACTIONSTRATEGY_H