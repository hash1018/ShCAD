
#ifndef _SHTOOLBARCONTAINEREVENTFILTER_H
#define _SHTOOLBARCONTAINEREVENTFILTER_H

class ShPropertyToolBar;
class ShNotifyEvent;
class ShPropertyToolBarEventFilterStrategy;

class ShPropertyToolBarEventFilter {

private:
	ShPropertyToolBarEventFilterStrategy *strategy;

public:
	ShPropertyToolBarEventFilter(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarEventFilter();

	void update();
};

///////////////////////////////////////////////////

class ShPropertyToolBarEventFilterStrategy {

protected:
	ShPropertyToolBar *propertyToolBar;
	ShNotifyEvent *event;

public:
	ShPropertyToolBarEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	virtual ~ShPropertyToolBarEventFilterStrategy() = 0;

	virtual void update() = 0;

};

///////////////////////////////////////////////////////////

class ShPropertyToolBarCurrentColorChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarCurrentColorChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarCurrentColorChangedEventFilterStrategy();

	void update();

};

//////////////////////////////////////////////////////////

class ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy();

	void update();

};

#endif //_SHTOOLBARCONTAINEREVENTFILTER_H