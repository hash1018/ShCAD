

#ifndef _SHDIMENSIONTOOLBAREVENTFILTER_H
#define _SHDIMENSIONTOOLBAREVENTFILTER_H

class ShNotifyEvent;
class ShDimensionToolBar;
class ShDimensionToolBarEventFilterStrategy;

class ShDimensionToolBarEventFilter {

private:
	ShDimensionToolBarEventFilterStrategy *strategy;

public:
	ShDimensionToolBarEventFilter(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event);
	~ShDimensionToolBarEventFilter();

	void update();
};


////////////////////////////////////////////////

class ShDimensionToolBarEventFilterStrategy {

protected:
	ShDimensionToolBar *dimensionToolBar;
	ShNotifyEvent *event;

public:
	ShDimensionToolBarEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event);
	~ShDimensionToolBarEventFilterStrategy();

	virtual void update() = 0;
};


//////////////////////////////////////////////////

class ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy : public ShDimensionToolBarEventFilterStrategy {

public:
	ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event);
	~ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy();

	virtual void update();
};

#endif //_SHDIMENSIONTOOLBAREVENTFILTER_H
