
#ifndef _SHTOOLBARCONTAINEREVENTFILTER_H
#define _SHTOOLBARCONTAINEREVENTFILTER_H

class ShPropertyToolBar;
class ShNotifyEvent;
class ShPropertyToolBarEventFilterStrategy;
class ShQuickAccessToolBar;
class ShQuickAccessToolBarEventFilterStrategy;
class ShLayerToolBar;
class ShLayerToolBarEventFilterStrategy;

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

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

class ShQuickAccessToolBarEventFilter {

private:
	ShQuickAccessToolBarEventFilterStrategy *strategy;

public:
	ShQuickAccessToolBarEventFilter(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event);
	~ShQuickAccessToolBarEventFilter();

	void update();
};

////////////////////////////////////////////////////

class ShQuickAccessToolBarEventFilterStrategy {

protected:
	ShQuickAccessToolBar *quickAccessToolBar;
	ShNotifyEvent *event;

public:
	ShQuickAccessToolBarEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event);
	virtual ~ShQuickAccessToolBarEventFilterStrategy() = 0;

	virtual void update() = 0;
};

/////////////////////////////////////////////////////

class ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy : public ShQuickAccessToolBarEventFilterStrategy {

public:
	ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event);
	~ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy();

	void update();
};

/////////////////////////////////////////////////////

class ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy : public ShQuickAccessToolBarEventFilterStrategy {

public:
	ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event);
	~ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy();

	void update();
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class ShLayerToolBarEventFilter {

private:
	ShLayerToolBarEventFilterStrategy *strategy;

public:
	ShLayerToolBarEventFilter(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarEventFilter();

	void update();
};

//////////////////////////////////////////////

class ShLayerToolBarEventFilterStrategy {

protected:
	ShLayerToolBar *layerToolBar;
	ShNotifyEvent *event;

public:
	ShLayerToolBarEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarEventFilterStrategy();

	virtual void update() = 0;
};

//////////////////////////////////////////////

class ShLayerToolBarActivatedWidgetChangedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarActivatedWidgetChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarActivatedWidgetChangedEventFilterStrategy();

	virtual void update();
};

/////////////////////////////////////////////

class ShLayerToolBarCurrentLayerChangedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarCurrentLayerChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarCurrentLayerChangedEventFilterStrategy();

	virtual void update();

};

/////////////////////////////////////////////

class ShLayerToolBarLayerDataChangedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarLayerDataChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarLayerDataChangedEventFilterStrategy();

	virtual void update();

};

#endif //_SHTOOLBARCONTAINEREVENTFILTER_H