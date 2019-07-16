
#ifndef _SHCADWIDGETEVENTFILTER_H
#define _SHCADWIDGETEVENTFILTER_H

class ShCADWidget;
class ShNotifyEvent;
class ShCADWidgetEventFilterStrategy;

class ShCADWidgetEventFilter {

private:
	ShCADWidgetEventFilterStrategy *strategy;

public:
	ShCADWidgetEventFilter(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetEventFilter();

	void update();

};


class ShCADWidgetEventFilterStrategy {

protected:
	ShNotifyEvent *event;
	ShCADWidget *widget;

public:
	ShCADWidgetEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	virtual ~ShCADWidgetEventFilterStrategy() = 0;

	virtual void update() = 0;

};

class ShCADWidgetKeyPressedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetKeyPressedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetKeyPressedEventFilterStrategy();

	virtual void update();

};

#endif //_SHCADWIDGETEVENTFILTER_H