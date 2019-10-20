
#ifndef _SHLAYERTOOLBAREVENTFILTER_H
#define _SHLAYERTOOLBAREVENTFILTER_H

class ShNotifyEvent;
class ShLayerToolBar;
class ShLayerToolBarEventFilterStrategy;

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

//////////////////////////////////////////////

class ShLayerToolBarLayerCreatedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarLayerCreatedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarLayerCreatedEventFilterStrategy();

	virtual void update();

};

///////////////////////////////////////////////

class ShLayerToolBarLayerDeletedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarLayerDeletedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarLayerDeletedEventFilterStrategy();

	virtual void update();

};

////////////////////////////////////////////////

class ShLayerToolBarActionChangedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarActionChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarActionChangedEventFilterStrategy();

	virtual void update();

};

////////////////////////////////////////////////

class ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy : public ShLayerToolBarEventFilterStrategy {

public:
	ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	~ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy();

	virtual void update();

};

#endif //_SHLAYERTOOLBAREVENTFILTER_H