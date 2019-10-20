
#ifndef _SHPROPERTYTOOLBAREVENTFILTER_H
#define _SHPROPERTYTOOLBAREVENTFILTER_H

class ShNotifyEvent;
class ShPropertyToolBar;
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

///////////////////////////////////////////////////////////

class ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy();

	void update();

};

///////////////////////////////////////////////////////////

class ShPropertyToolBarCurrentLayerChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarCurrentLayerChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarCurrentLayerChangedEventFilterStrategy();

	void update();

};


/////////////////////////////////////////////////////////

class ShPropertyToolBarLayerDataChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarLayerDataChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarLayerDataChangedEventFilterStrategy();

	void update();

};

//////////////////////////////////////////////////////////

class ShPropertyToolBarActionChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarActionChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarActionChangedEventFilterStrategy();

	void update();

};

///////////////////////////////////////////////////////////

class ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy : public ShPropertyToolBarEventFilterStrategy {

public:
	ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	~ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy();

	void update();

};

#endif //_SHPROPERTYTOOLBAREVENTFILTER_H