

#ifndef _SHCOMMANDDOCKEVENTFILTER_H
#define _SHCOMMANDDOCKEVENTFILTER_H

class ShCommandDock;
class ShNotifyEvent;
class ShCommandDockEventFilterStrategy;

class ShCommandDockEventFilter {

private:
	ShCommandDockEventFilterStrategy *strategy;

public:
	ShCommandDockEventFilter(ShCommandDock *commandDock, ShNotifyEvent *event);
	~ShCommandDockEventFilter();

	void update();

};


class ShCommandDockEventFilterStrategy {

protected:
	ShNotifyEvent *event;
	ShCommandDock *commandDock;

public:
	ShCommandDockEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event);
	virtual ~ShCommandDockEventFilterStrategy() = 0;

	virtual void update() = 0;

};

class ShCommandDockKeyPressedEventFilterStrategy : public ShCommandDockEventFilterStrategy {

public:
	ShCommandDockKeyPressedEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event);
	~ShCommandDockKeyPressedEventFilterStrategy();

	virtual void update();

};


class ShCommandDockActivatedWidgetChangedEventFilterStrategy : public ShCommandDockEventFilterStrategy {

public:
	ShCommandDockActivatedWidgetChangedEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event);
	~ShCommandDockActivatedWidgetChangedEventFilterStrategy();

	virtual void update();
};


#endif //_SHCOMMANDDOCKEVENTFILTER_H