
#ifndef _SHQUICKACCESSTOOLBAREVENTFILTER_H
#define _SHQUICKACCESSTOOLBAREVENTFILTER_H

class ShQuickAccessToolBar;
class ShNotifyEvent;
class ShQuickAccessToolBarEventFilterStrategy;

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

#endif //_SHQUICKACCESSTOOLBAREVENTFILTER_H