
#ifndef _SHSTATUSBAREVENTFILTER_H
#define _SHSTATUSBAREVENTFILTER_H

class ShStatusBar;
class ShNotifyEvent;
class ShStatusBarEventFilterStrategy;

class ShStatusBarEventFilter {

private:
	ShStatusBarEventFilterStrategy *strategy;

public:
	ShStatusBarEventFilter(ShStatusBar *statusBar, ShNotifyEvent *event);
	~ShStatusBarEventFilter();

	void update();

};

/////////////////////////////////////////////////////////////////

class ShStatusBarEventFilterStrategy {

protected:
	ShStatusBar *statusBar;
	ShNotifyEvent *event;

public:
	ShStatusBarEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event);
	virtual ~ShStatusBarEventFilterStrategy() = 0;

	virtual void update() = 0;

};

///////////////////////////////////////////////////////////////////

class ShStatusBarMousePositionChangedEventFilterStrategy : public ShStatusBarEventFilterStrategy {

public:
	ShStatusBarMousePositionChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event);
	~ShStatusBarMousePositionChangedEventFilterStrategy();

	virtual void update();

};

class ShStatusBarZoomRateChangedEventFilterStrategy : public ShStatusBarEventFilterStrategy {

public:
	ShStatusBarZoomRateChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event);
	~ShStatusBarZoomRateChangedEventFilterStrategy();

	virtual void update();

};

class ShStatusBarActivatedWidgetChangedEventFilterStrategy : public ShStatusBarEventFilterStrategy {

public:
	ShStatusBarActivatedWidgetChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event);
	~ShStatusBarActivatedWidgetChangedEventFilterStrategy();

	virtual void update();

};

#endif //_SHSTATUSBAREVENTFILTER_H