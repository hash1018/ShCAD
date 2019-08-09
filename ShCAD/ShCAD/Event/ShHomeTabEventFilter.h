
#ifndef _SHHOMETABEVENTFILTER_H
#define _SHHOMETABEVENTFILTER_H

class ShPropertyPanel;
class ShNotifyEvent;
class ShPropertyPanelEventFilterStrategy;

class ShPropertyPanelEventFilter {

private:
	ShPropertyPanelEventFilterStrategy *strategy;

public:
	ShPropertyPanelEventFilter(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	~ShPropertyPanelEventFilter();

	void update();
};

///////////////////////////////////////////////////

class ShPropertyPanelEventFilterStrategy {

protected:
	ShPropertyPanel *propertyPanel;
	ShNotifyEvent *event;

public:
	ShPropertyPanelEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	virtual ~ShPropertyPanelEventFilterStrategy() = 0;

	virtual void update() = 0;

};

///////////////////////////////////////////////////////////

class ShPropertyPanelCurrentColorChangedEventFilterStrategy : public ShPropertyPanelEventFilterStrategy {

public:
	ShPropertyPanelCurrentColorChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	~ShPropertyPanelCurrentColorChangedEventFilterStrategy();

	void update();

};

//////////////////////////////////////////////////////////

class ShPropertyPanelActivatedWidgetChangedEventFilterStrategy : public ShPropertyPanelEventFilterStrategy {

public:
	ShPropertyPanelActivatedWidgetChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	~ShPropertyPanelActivatedWidgetChangedEventFilterStrategy();

	void update();

};

#endif //_SHHOMETABEVENTFILTER_H