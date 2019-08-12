
#ifndef _SHHOMETABEVENTFILTER_H
#define _SHHOMETABEVENTFILTER_H

class ShPropertyPanel;
class ShNotifyEvent;
class ShPropertyPanelEventFilterStrategy;
class ShLayerPanel;
class ShLayerPanelEventFilterStrategy;

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

///////////////////////////////////////////////////////////

class ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy : public ShPropertyPanelEventFilterStrategy {

public:
	ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	~ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy();

	void update();

};

//////////////////////////////////////////////////////////

class ShPropertyPanelCurrentLayerChangedEventFilterStrategy : public ShPropertyPanelEventFilterStrategy {

public:
	ShPropertyPanelCurrentLayerChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event);
	~ShPropertyPanelCurrentLayerChangedEventFilterStrategy();

	void update();

};


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

class ShLayerPanelEventFilter {

private:
	ShLayerPanelEventFilterStrategy *strategy;

public:
	ShLayerPanelEventFilter(ShLayerPanel *layerPanel, ShNotifyEvent *event);
	~ShLayerPanelEventFilter();

	void update();
};

//////////////////////////////////////////////

class ShLayerPanelEventFilterStrategy {

protected:
	ShLayerPanel *layerPanel;
	ShNotifyEvent *event;

public:
	ShLayerPanelEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event);
	~ShLayerPanelEventFilterStrategy();

	virtual void update() = 0;
};

//////////////////////////////////////////////

class ShLayerPanelActivatedWidgetChangedEventFilterStrategy : public ShLayerPanelEventFilterStrategy {

public:
	ShLayerPanelActivatedWidgetChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event);
	~ShLayerPanelActivatedWidgetChangedEventFilterStrategy();

	virtual void update();
};

////////////////////////////////////////////////

class ShLayerPanelCurrentLayerChangedEventFilterStrategy : public ShLayerPanelEventFilterStrategy {

public:
	ShLayerPanelCurrentLayerChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event);
	~ShLayerPanelCurrentLayerChangedEventFilterStrategy();

	virtual void update();

};

#endif //_SHHOMETABEVENTFILTER_H