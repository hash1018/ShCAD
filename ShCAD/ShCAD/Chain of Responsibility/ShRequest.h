
#ifndef _SHREQUEST_H
#define _SHREQUEST_H

class ShChangeActionStrategy;
class ShNotifyEvent;

class ShRequest {

public:
	enum RequestType {
		RequestCreateNewCADWidget,
		RequestChangeActionHandler,
		RequestSendNotifyEvent,
		RequestUndo,
		RequestRedo,
		RequestChangeViewMode,

	};

protected:
	RequestType type;

public:
	ShRequest(RequestType type);
	virtual ~ShRequest() = 0;

	inline RequestType getType() const { return this->type; }

};

class ShRequestCreateNewCADWidget : public ShRequest {

public:
	ShRequestCreateNewCADWidget();
	~ShRequestCreateNewCADWidget();

};

class ShRequestChangeActionHandler : public ShRequest {

private:
	ShChangeActionStrategy *strategy;

public:
	ShRequestChangeActionHandler(ShChangeActionStrategy *strategy);
	~ShRequestChangeActionHandler();

	inline ShChangeActionStrategy* getStrategy() const { return this->strategy; }
};

class ShRequestSendNotifyEvent : public ShRequest {

private:
	ShNotifyEvent *notifyEvent;

public:
	ShRequestSendNotifyEvent(ShNotifyEvent *notifyEvent);
	~ShRequestSendNotifyEvent();

	inline ShNotifyEvent* getNotifyEvent() const { return this->notifyEvent; }
};

class ShRequestUndo : public ShRequest {

public:
	ShRequestUndo();
	~ShRequestUndo();

};

class ShRequestRedo : public ShRequest {

public:
	ShRequestRedo();
	~ShRequestRedo();

};

class ShRequestChangeViewMode : public ShRequest {

public:
	enum ViewMode {
		SubWindowView,
		TabbedView,
		Cascade,
		Tile,
		
	};

private:
	ViewMode viewMode;

public:
	ShRequestChangeViewMode(ViewMode viewMode);
	~ShRequestChangeViewMode();

	inline ViewMode getViewMode() const { return this->viewMode; }

};

#endif //_SHREQUEST_H